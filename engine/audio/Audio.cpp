// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#include <algorithm>
#include "../core/Setup.h"
#include "Audio.hpp"
#include "AudioDevice.hpp"
#include "Listener.hpp"
#include "alsa/ALSAAudioDevice.hpp"
#include "coreaudio/CAAudioDevice.hpp"
#include "dsound/DSAudioDevice.hpp"
#include "empty/EmptyAudioDevice.hpp"
#include "openal/OALAudioDevice.hpp"
#include "opensl/OSLAudioDevice.hpp"
#include "xaudio2/XA2AudioDevice.hpp"
#include "wasapi/WASAPIAudioDevice.hpp"
#include "../core/Engine.hpp"
#include "../utils/Log.hpp"

namespace ouzel::audio
{
    Driver Audio::getDriver(const std::string& driver)
    {
        if (driver.empty() || driver == "default")
        {
            auto availableDrivers = Audio::getAvailableAudioDrivers();

            if (availableDrivers.find(Driver::wasapi) != availableDrivers.end())
                return Driver::wasapi;
            else if (availableDrivers.find(Driver::coreAudio) != availableDrivers.end())
                return Driver::coreAudio;
            else if (availableDrivers.find(Driver::alsa) != availableDrivers.end())
                return Driver::alsa;
            else if (availableDrivers.find(Driver::openAL) != availableDrivers.end())
                return Driver::openAL;
            else if (availableDrivers.find(Driver::xAudio2) != availableDrivers.end())
                return Driver::xAudio2;
            else if (availableDrivers.find(Driver::directSound) != availableDrivers.end())
                return Driver::directSound;
            else if (availableDrivers.find(Driver::openSL) != availableDrivers.end())
                return Driver::openSL;
            else
                return Driver::empty;
        }
        else if (driver == "empty")
            return Driver::empty;
        else if (driver == "openal")
            return Driver::openAL;
        else if (driver == "directsound")
            return Driver::directSound;
        else if (driver == "xaudio2")
            return Driver::xAudio2;
        else if (driver == "opensl")
            return Driver::openSL;
        else if (driver == "coreaudio")
            return Driver::coreAudio;
        else if (driver == "alsa")
            return Driver::alsa;
        else if (driver == "wasapi")
            return Driver::wasapi;
        else
            throw std::runtime_error("Invalid audio driver");
    }

    std::set<Driver> Audio::getAvailableAudioDrivers()
    {
        static std::set<Driver> availableDrivers;

        if (availableDrivers.empty())
        {
            availableDrivers.insert(Driver::empty);

#if OUZEL_COMPILE_OPENAL
            availableDrivers.insert(Driver::openAL);
#endif
#if OUZEL_COMPILE_DIRECTSOUND
            availableDrivers.insert(Driver::directSound);
#endif
#if OUZEL_COMPILE_XAUDIO2
            availableDrivers.insert(Driver::xAudio2);
#endif
#if OUZEL_COMPILE_OPENSL
            availableDrivers.insert(Driver::openSL);
#endif
#if OUZEL_COMPILE_COREAUDIO
            availableDrivers.insert(Driver::coreAudio);
#endif
#if OUZEL_COMPILE_ALSA
            availableDrivers.insert(Driver::alsa);
#endif
#if OUZEL_COMPILE_WASAPI
            availableDrivers.insert(Driver::wasapi);
#endif
        }

        return availableDrivers;
    }

    namespace
    {
        std::unique_ptr<AudioDevice> createAudioDevice(Driver driver,
                                                       const std::function<void(std::uint32_t frames, std::uint32_t channels, std::uint32_t sampleRate, std::vector<float>& samples)>& dataGetter,
                                                       bool debugAudio)
        {
            switch (driver)
            {
#if OUZEL_COMPILE_OPENAL
                case Driver::openAL:
                    engine->log(Log::Level::info) << "Using OpenAL audio driver";
                    return std::make_unique<openal::AudioDevice>(512, 44100, 0, dataGetter);
#endif
#if OUZEL_COMPILE_DIRECTSOUND
                case Driver::directSound:
                    engine->log(Log::Level::info) << "Using DirectSound audio driver";
                    return std::make_unique<directsound::AudioDevice>(512, 44100, 0, dataGetter);
#endif
#if OUZEL_COMPILE_XAUDIO2
                case Driver::xAudio2:
                    engine->log(Log::Level::info) << "Using XAudio 2 audio driver";
                    return std::make_unique<xaudio2::AudioDevice>(512, 44100, 0, dataGetter, debugAudio);
#endif
#if OUZEL_COMPILE_OPENSL
                case Driver::openSL:
                    engine->log(Log::Level::info) << "Using OpenSL ES audio driver";
                    return std::make_unique<opensl::AudioDevice>(512, 44100, 0, dataGetter);
#endif
#if OUZEL_COMPILE_COREAUDIO
                case Driver::coreAudio:
                    engine->log(Log::Level::info) << "Using CoreAudio audio driver";
                    return std::make_unique<coreaudio::AudioDevice>(512, 44100, 0, dataGetter);
#endif
#if OUZEL_COMPILE_ALSA
                case Driver::alsa:
                    engine->log(Log::Level::info) << "Using ALSA audio driver";
                    return std::make_unique<alsa::AudioDevice>(512, 44100, 0, dataGetter);
#endif
#if OUZEL_COMPILE_WASAPI
                case Driver::wasapi:
                    engine->log(Log::Level::info) << "Using WASAPI audio driver";
                    return std::make_unique<wasapi::AudioDevice>(512, 44100, 0, dataGetter);
#endif
                default:
                    engine->log(Log::Level::info) << "Not using audio driver";
                    static_cast<void>(debugAudio);
                    return std::make_unique<empty::AudioDevice>(512, 44100, 0, dataGetter);
            }
        }
    }

    Audio::Audio(Driver driver, bool debugAudio):
        device(createAudioDevice(driver,
                                 std::bind(&Audio::getSamples, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4),
                                 debugAudio)),
        mixer(device->getBufferSize(), device->getChannels(),
              std::bind(&Audio::eventCallback, this, std::placeholders::_1)),
        masterMix(*this),
        rootNode(*this) // mixer.getRootObjectId()
    {
        addCommand(std::make_unique<mixer::SetMasterBusCommand>(masterMix.getBusId()));
        device->start();
    }

    void Audio::update()
    {
        // TODO: handle events from the audio device

        mixer.submitCommandBuffer(std::move(commandBuffer));
        commandBuffer = mixer::CommandBuffer();
    }

    void Audio::deleteObject(std::size_t objectId)
    {
        addCommand(std::make_unique<mixer::DeleteObjectCommand>(objectId));
    }

    std::size_t Audio::initBus()
    {
        std::size_t busId = mixer.getObjectId();
        addCommand(std::make_unique<mixer::InitBusCommand>(busId));
        return busId;
    }

    std::size_t Audio::initStream(std::size_t sourceId)
    {
        std::size_t streamId = mixer.getObjectId();
        addCommand(std::make_unique<mixer::InitStreamCommand>(streamId, sourceId));
        return streamId;
    }

    std::size_t Audio::initData(std::unique_ptr<mixer::Data> data)
    {
        std::size_t dataId = mixer.getObjectId();
        addCommand(std::make_unique<mixer::InitDataCommand>(dataId, std::move(data)));
        return dataId;
    }

    std::size_t Audio::initProcessor(std::unique_ptr<mixer::Processor> processor)
    {
        std::size_t processorId = mixer.getObjectId();
        addCommand(std::make_unique<mixer::InitProcessorCommand>(processorId, std::move(processor)));
        return processorId;
    }

    void Audio::updateProcessor(std::size_t processorId, const std::function<void(mixer::Processor*)>& updateFunction)
    {
        addCommand(std::make_unique<mixer::UpdateProcessorCommand>(processorId, updateFunction));
    }

    void Audio::getSamples(std::uint32_t frames, std::uint32_t channels, std::uint32_t sampleRate, std::vector<float>& samples)
    {
        mixer.getSamples(frames, channels, sampleRate, samples);
    }

    void Audio::eventCallback(const mixer::Mixer::Event&)
    {
    }
}

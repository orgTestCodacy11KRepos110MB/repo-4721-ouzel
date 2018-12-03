// Copyright 2015-2018 Elviss Strazdins. All rights reserved.

#include "Reverb.hpp"
#include "Audio.hpp"

namespace ouzel
{
    namespace audio
    {
        class ReverbProcessor final: public Processor
        {
        public:
            ReverbProcessor()
            {
            }

            void process(std::vector<float>& samples, uint16_t& channels,
                         uint32_t& sampleRate, Vector3& position) override
            {
            }
        };

        Reverb::Reverb(Audio& initAudio):
            Filter(initAudio,
                   initAudio.initProcessor(std::unique_ptr<Processor>(new ReverbProcessor())))
        {
        }

        Reverb::~Reverb()
        {
        }
    } // namespace audio
} // namespace ouzel


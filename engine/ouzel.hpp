// Copyright 2015-2020 Elviss Strazdins. All rights reserved.

#ifndef OUZEL_HPP
#define OUZEL_HPP

#include "assets/Bundle.hpp"
#include "assets/Cache.hpp"
#include "assets/Loader.hpp"
#include "assets/BmfLoader.hpp"
#include "assets/ColladaLoader.hpp"
#include "assets/GltfLoader.hpp"
#include "assets/ImageLoader.hpp"
#include "assets/MtlLoader.hpp"
#include "assets/ObjLoader.hpp"
#include "assets/ParticleSystemLoader.hpp"
#include "assets/SpriteLoader.hpp"
#include "assets/TtfLoader.hpp"
#include "assets/VorbisLoader.hpp"
#include "assets/WaveLoader.hpp"
#include "audio/Audio.hpp"
#include "audio/AudioDevice.hpp"
#include "audio/Channel.hpp"
#include "audio/Containers.hpp"
#include "audio/Cue.hpp"
#include "audio/Driver.hpp"
#include "audio/Effect.hpp"
#include "audio/Effects.hpp"
#include "audio/Listener.hpp"
#include "audio/Mix.hpp"
#include "audio/Node.hpp"
#include "audio/Oscillator.hpp"
#include "audio/PcmClip.hpp"
#include "audio/SampleFormat.hpp"
#include "audio/SilenceSound.hpp"
#include "audio/Sound.hpp"
#include "audio/Source.hpp"
#include "audio/Submix.hpp"
#include "audio/Voice.hpp"
#include "audio/VorbisClip.hpp"
#include "audio/WavePlayer.hpp"
#include "core/Setup.h"
#include "core/Engine.hpp"
#include "core/Timer.hpp"
#include "core/Window.hpp"
#include "events/Event.hpp"
#include "events/EventDispatcher.hpp"
#include "events/EventHandler.hpp"
#include "graphics/BlendFactor.hpp"
#include "graphics/BlendOperation.hpp"
#include "graphics/BlendState.hpp"
#include "graphics/Buffer.hpp"
#include "graphics/BufferType.hpp"
#include "graphics/ColorMask.hpp"
#include "graphics/Commands.hpp"
#include "graphics/CompareFunction.hpp"
#include "graphics/CubeFace.hpp"
#include "graphics/DataType.hpp"
#include "graphics/DepthStencilState.hpp"
#include "graphics/DrawMode.hpp"
#include "graphics/Driver.hpp"
#include "graphics/Flags.hpp"
#include "graphics/Graphics.hpp"
#include "graphics/Image.hpp"
#include "graphics/Material.hpp"
#include "graphics/Object.hpp"
#include "graphics/PixelFormat.hpp"
#include "graphics/RasterizerState.hpp"
#include "graphics/RenderDevice.hpp"
#include "graphics/RenderTarget.hpp"
#include "graphics/SamplerAddressMode.hpp"
#include "graphics/SamplerFilter.hpp"
#include "graphics/Shader.hpp"
#include "graphics/StencilOperation.hpp"
#include "graphics/Texture.hpp"
#include "graphics/TextureType.hpp"
#include "graphics/Vertex.hpp"
#include "gui/BMFont.hpp"
#include "gui/TTFont.hpp"
#include "gui/Widget.hpp"
#include "gui/Widgets.hpp"
#include "input/Controller.hpp"
#include "input/Cursor.hpp"
#include "input/Gamepad.hpp"
#include "input/InputManager.hpp"
#include "input/InputSystem.hpp"
#include "input/Keyboard.hpp"
#include "input/Mouse.hpp"
#include "input/Touchpad.hpp"
#include "localization/Localization.hpp"
#include "math/Box.hpp"
#include "math/Color.hpp"
#include "math/Constants.hpp"
#include "math/ConvexVolume.hpp"
#include "math/Fnv.hpp"
#include "math/MathUtils.hpp"
#include "math/Matrix.hpp"
#include "math/Plane.hpp"
#include "math/Quaternion.hpp"
#include "math/Rect.hpp"
#include "math/Size.hpp"
#include "math/Vector.hpp"
#include "network/Client.hpp"
#include "network/Network.hpp"
#include "network/Server.hpp"
#include "network/Socket.hpp"
#include "scene/Actor.hpp"
#include "scene/Animator.hpp"
#include "scene/Animators.hpp"
#include "scene/Camera.hpp"
#include "scene/Component.hpp"
#include "scene/Layer.hpp"
#include "scene/Light.hpp"
#include "scene/ParticleSystem.hpp"
#include "scene/Scene.hpp"
#include "scene/SceneManager.hpp"
#include "scene/ShapeRenderer.hpp"
#include "scene/SpriteRenderer.hpp"
#include "scene/SkinnedMeshRenderer.hpp"
#include "scene/StaticMeshRenderer.hpp"
#include "scene/TextRenderer.hpp"
#include "storage/Archive.hpp"
#include "storage/FileSystem.hpp"
#include "storage/Path.hpp"
#include "utils/Ini.hpp"
#include "utils/Json.hpp"
#include "utils/Log.hpp"
#include "utils/Obf.hpp"
#include "utils/Utf8.hpp"
#include "utils/Utils.hpp"
#include "utils/Xml.hpp"

#endif // OUZEL_HPP

#pragma once

#include "Codec.h"
#include "PacketBuffer.h"


#include <memory>


//
// Element.Inputs[]
// Element.Outputs[]

enum class PinDirection
{
	Out = 0,
	In
};

enum class MediaCategory
{
	Unknown = 0,
	Audio,
	Video,
	Subtitle
};

enum class VideoStreamType
{
	Unknown = 0,
	Mpeg2,
	Mpeg4,
	Avc,
	VC1,
	Hevc
};

enum class AudioStreamType
{
	Unknown = 0,
	Pcm,
	Mpeg2Layer3,
	Ac3,
	Dts
};

enum class SubtitleStreamType
{
	Unknown = 0,
	Text
};


class PinInfo
{
	MediaCategory category;

public:

	MediaCategory Category() const
	{
		return category;
	}


	PinInfo(MediaCategory category)
		: category(category)
	{
	}
};
typedef std::shared_ptr<PinInfo> PinInfoSPTR;

class VideoPinInfo : public PinInfo
{
public:
	VideoPinInfo()
		: PinInfo(MediaCategory::Video)
	{
	}

	VideoStreamType StreamType = VideoStreamType::Unknown;
	double FrameRate = 0;
};
typedef std::shared_ptr<VideoPinInfo> VideoPinInfoSPTR;

class AudioPinInfo : public PinInfo
{

public:
	AudioPinInfo()
		: PinInfo(MediaCategory::Audio)
	{
	}


	AudioStreamType StreamType = AudioStreamType::Unknown;
	int Channels = 0;
	int SampleRate = 0;


};
typedef std::shared_ptr<AudioPinInfo> AudioPinInfoSPTR;

class SubtitlePinInfo : public PinInfo
{
public:

	SubtitlePinInfo()
		: PinInfo(MediaCategory::Subtitle)
	{
	}


	SubtitleStreamType StreamType = SubtitleStreamType::Unknown;
};
typedef std::shared_ptr<SubtitlePinInfo> SubtitlePinInfoSPTR;


class Pin : public std::enable_shared_from_this<Pin>
{
	PinDirection direction;
	ElementWPTR owner;
	PinInfoSPTR info;


protected:
	Pin(PinDirection direction, ElementWPTR owner, PinInfoSPTR info)
		: direction(direction), owner(owner), info(info)
	{
		if (owner.expired())
			throw ArgumentNullException();

		if (!info)
			throw ArgumentNullException();
	}


public:

	PinDirection Direction() const
	{
		return direction;
	}

	ElementWPTR Owner() const
	{
		return owner;
	}

	PinInfoSPTR Info() const
	{
		return info;
	}


	virtual ~Pin()
	{
	}


	virtual void Flush()
	{
	}
};

//typedef std::shared_ptr<Pin> PinSPTR;
//
//
//class InPin;
//typedef std::shared_ptr<InPin> InPinSPTR;
//
//class OutPin;
//typedef std::shared_ptr<OutPin> OutPinSPTR;
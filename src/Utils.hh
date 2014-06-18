/*
 *  Utils.hh - Different utils
 *  Copyright (C) 2014  Fundació i2CAT, Internet i Innovació digital a Catalunya
 *
 *  This file is part of liveMediaStreamer.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Authors:  Marc Palau <marc.palau@i2cat.net>
 */

#ifndef _UTILS_HH
#define _UTILS_HH

#include "Types.hh"
#include <string>

#define ID_LENGTH 4

namespace utils 
{
    SampleFmt getSampleFormatFromString(std::string stringSampleFmt);
    ACodecType getCodecFromString(std::string stringCodec);
    std::string getAudioCodecAsString(ACodecType codec);
    std::string getFilterTypeAsString(FilterType type);
    std::string getSampleFormatAsString(SampleFmt sFormat);
	std::string randomIdGenerator(unsigned int length);
}

#endif
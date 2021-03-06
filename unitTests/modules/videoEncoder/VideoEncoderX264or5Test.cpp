/*
 *  VideoEncoderX264or5Test.cpp - VideoEncoderX264or5 class test
 *  Copyright (C) 2015  Fundació i2CAT, Internet i Innovació digital a Catalunya
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
 *            David Cassany <david.cassany@i2cat.net>
 *            Gerard Castillo <gerard.castillo@i2cat.net>
 *
 */

#include <string>
#include <iostream>
#include <fstream>

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/XmlOutputter.h>

#include "modules/videoEncoder/VideoEncoderX264or5.hh"

class VideoEncoderX264or5Mock : public VideoEncoderX264or5 
{
public:
    VideoEncoderX264or5Mock() : VideoEncoderX264or5(MASTER, true) {};
    ~VideoEncoderX264or5Mock(){};
    bool fillPicturePlanes(unsigned char** data, int* linesize) {return fillPicturePlanesRetVal;};
    bool encodeFrame(VideoFrame* codedFrame) {return encodeFrameRetVal;};
    bool reconfigure(VideoFrame* orgFrame, VideoFrame* dstFrame) {return reconfigureRetVal;};
    void setFillPicturePlanesRetVal(bool val) {fillPicturePlanesRetVal = val;};
    void setEncodeFrameRetVal(bool val) {encodeFrameRetVal = val;};
    void setReconfigureRetVal(bool val) {reconfigureRetVal = val;};
    FrameQueue *allocQueue(int wId) {return NULL;};

private:
    bool fillPicturePlanesRetVal;
    bool encodeFrameRetVal;
    bool reconfigureRetVal;
};

class VideoEncoderX264or5Test : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(VideoEncoderX264or5Test);
    CPPUNIT_TEST(configureTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

protected:
    void configureTest();

    VideoEncoderX264or5Mock* encoder;
};

void VideoEncoderX264or5Test::setUp()
{
    encoder = new VideoEncoderX264or5Mock();
}

void VideoEncoderX264or5Test::tearDown()
{
    delete encoder;
}

void VideoEncoderX264or5Test::configureTest()
{
    int goodBitrate = 2000;
    int badBitrate = 0;
    int goodGop = 25;
    int badGop = 0;
    int goodLookahead1 = 0;
    int goodLookahead2 = 10;
    int badLookahead = -2;
    int goodThreads = 2;
    int badThreads = 0;
    int annexb = true;
    int fps1 = 0;
    int fps2 = 25;
    std::string emptyPreset;
    std::string goodPreset = "superfast";

    CPPUNIT_ASSERT(!encoder->configure(badBitrate, fps1, goodGop, goodLookahead1, goodThreads, annexb, goodPreset));
    CPPUNIT_ASSERT(!encoder->configure(goodBitrate, fps1, badGop, goodLookahead1, goodThreads, annexb, goodPreset));
    CPPUNIT_ASSERT(!encoder->configure(goodBitrate, fps1, goodGop, badLookahead, goodThreads, annexb, goodPreset));
    CPPUNIT_ASSERT(!encoder->configure(goodBitrate, fps1, goodGop, goodLookahead1, badThreads, annexb, goodPreset));
    CPPUNIT_ASSERT(!encoder->configure(goodBitrate, fps1, goodGop, goodLookahead1, goodThreads, annexb, emptyPreset));
    CPPUNIT_ASSERT(encoder->configure(goodBitrate, fps1, goodGop, goodLookahead1, goodThreads, annexb, goodPreset));
    CPPUNIT_ASSERT(encoder->configure(goodBitrate, fps1, goodGop, goodLookahead2, goodThreads, annexb, goodPreset));
    CPPUNIT_ASSERT(encoder->configure(goodBitrate, fps1, goodGop, goodLookahead1, goodThreads, annexb, goodPreset));
    CPPUNIT_ASSERT(encoder->configure(goodBitrate, fps2, goodGop, goodLookahead1, goodThreads, annexb, goodPreset));
}

CPPUNIT_TEST_SUITE_REGISTRATION(VideoEncoderX264or5Test);

int main(int argc, char* argv[])
{
    std::ofstream xmlout("VideoEncoderX264or5Test.xml");
    CPPUNIT_NS::TextTestRunner runner;
    CPPUNIT_NS::XmlOutputter *outputter = new CPPUNIT_NS::XmlOutputter(&runner.result(), xmlout);

    runner.addTest( CppUnit::TestFactoryRegistry::getRegistry().makeTest() );
    runner.run( "", false );
    outputter->write();

    utils::printMood(runner.result().wasSuccessful());

    return runner.result().wasSuccessful() ? 0 : 1;
}

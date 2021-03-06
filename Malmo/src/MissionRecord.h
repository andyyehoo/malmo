// --------------------------------------------------------------------------------------------------
//  Copyright (c) 2016 Microsoft Corporation
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
//  associated documentation files (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge, publish, distribute,
//  sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all copies or
//  substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
//  NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
//  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
//  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
// --------------------------------------------------------------------------------------------------

#ifndef _MISSIONRECORD_H_
#define _MISSIONRECORD_H_

// Local:
#include "Tarball.hpp"
#include "MissionRecordSpec.h"

// Boost:
#include <boost/filesystem.hpp>

// STL:
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace malmo
{
    //! Handles the mission record file.
    class MissionRecord
    {
        public:        
            //! Constructs a mission record handler with the provided specification
            MissionRecord(const MissionRecordSpec& spec);

            MissionRecord(MissionRecord&& record);
            MissionRecord& operator= (MissionRecord&& record);

            MissionRecord(const MissionRecord&) = delete;
            MissionRecord& operator= (const MissionRecord&) = delete;
            
            //! Finalizes the mission record, closing the record if that has not already been performed.
            ~MissionRecord();

            //! Saves the recording to file.
            //! Only call this once per instance of MissionRecord, after all the missions have finished,
            //! else the paths returned by e.g. getVideoPath() will be invalid.
            void close();

            //! Gets whether the mission will be recorded or not.
            //! \returns Boolean value.
            bool isRecording() const;

            //! Gets whether the video from the mission will be recorded or not.
            //! \returns Boolean value.
            bool isRecordingMP4() const;

            //! Gets whether the observations from the mission will be recorded or not.
            //! \returns Boolean value.
            bool isRecordingObservations() const;

            //! Gets whether the rewards from the mission will be recorded or not.
            //! \returns Boolean value.
            bool isRecordingRewards() const;

            //! Gets whether the commands sent during the mission will be recorded or not.
            //! \returns Boolean value.
            bool isRecordingCommands() const;

            //! Gets the path where the mp4 video should be saved to, if recording has been requested.
            //! \returns The path as a string.
            std::string getMP4Path() const;

            //! Gets the bitrate at which the video should be recorded, if MP4 recording has been requested.
            //! \returns The bitrate in bits per second.
            int64_t getMP4BitRate() const;

            //! Gets the frequency at which frames should be recorded, if MP4 recording has been requested.
            //! \returns The frames per second.
            int getMP4FramesPerSecond() const;

            //! Gets the path where the observations should be saved to, if recording has been requested.
            //! \returns The path as a string.
            std::string getObservationsPath() const;

            //! Gets the path where the rewards should be saved to, if recording has been requested.
            //! \returns The path as a string.
            std::string getRewardsPath() const;

            //! Gets the path where the commands should be saved to, if recording has been requested.
            //! \returns The path as a string.
            std::string getCommandsPath() const;

            //! Gets the path where the mission init should be saved to
            //! \returns The path as a string
            std::string getMissionInitPath() const;

        private:

            bool is_closed;
            MissionRecordSpec spec;

            void addFiles(std::vector<boost::filesystem::path> &fileList, boost::filesystem::path directory);
            void addFile(lindenb::io::Tar& archive, boost::filesystem::path path);
    };
}

#endif

#include "flv-reader.h"
#include "flv-writer.h"
#include "flv-demuxer.h"
#include "flv-muxer.h"
#include "flv-proto.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;


static int flv_onmuxer(void* flv, int type, const void* data, size_t bytes, uint32_t timestamp)
{
	return flv_writer_input(flv, type, data, bytes, timestamp);
}

static int flv_ondemuxer(void* param, int codec, const void* data, size_t bytes, uint32_t pts, uint32_t dts, int flags)
{
    bool static first_keyframe_added = false;

	flv_muxer_t* muxer = (flv_muxer_t*)param;
	switch (codec)
	{
	case FLV_AUDIO_AAC:
		flv_muxer_aac(muxer, data, bytes, pts, dts);
		break;

	case FLV_AUDIO_MP3:
		flv_muxer_mp3(muxer, data, bytes, pts, dts);
		break;
	case FLV_VIDEO_H264:
        if (!first_keyframe_added){
            first_keyframe_added = true;
        }else{
            if (flags == 1) break;   // keyframe            
        }
		flv_muxer_avc(muxer, data, bytes, pts, dts);
		break;

	case FLV_VIDEO_H265:
        if (!first_keyframe_added){
            first_keyframe_added = true;
        }else{
            if (flags == 1) break;   // keyframe            
        }
		flv_muxer_hevc(muxer, data, bytes, pts, dts);
		break;

	case FLV_VIDEO_AV1:
        if (!first_keyframe_added){
            first_keyframe_added = true;
        }else{
            if (flags == 1) break;   // keyframe            
        }
		flv_muxer_av1(muxer, data, bytes, pts, dts);
		break;

	default:
		break;
	}
	return 0;
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        cout << "pls specify input flv filename." << endl;
        return 1;
    }

    string file_input  = argv[1];
    string file_output = file_input;
    string::size_type p = file_output.rfind(".");
    if (p != string::npos){
        file_output = file_output.substr(0, p) + "_no_keyframe.flv";
    }else{
        file_output = file_output + "_no_keyframe.flv";
    }


	static char packet[2 * 1024 * 1024];


	void* r = flv_reader_create(file_input.c_str());
	void* w = flv_writer_create(file_output.c_str());
	flv_muxer_t* e = flv_muxer_create(flv_onmuxer, w);
	flv_demuxer_t* d = flv_demuxer_create(flv_ondemuxer, e);


	int ret, tag;
	size_t taglen;
	uint32_t timestamp;
	while (1 == flv_reader_read(r, &tag, &timestamp, &taglen, packet, sizeof(packet)))
	{
		ret = flv_demuxer_input(d, tag, packet, taglen, timestamp);
		assert(0 == ret);
	}

	flv_muxer_destroy(e);
	flv_demuxer_destroy(d);
	flv_reader_destroy(r);
	flv_writer_destroy(w);
}

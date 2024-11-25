// video_converter.h
#ifndef VIDEO_CONVERTER_H
#define VIDEO_CONVERTER_H

#include "config.h"
#include "image_converter.h"

// Video frame representation
typedef struct {
    unsigned char *data;  // Raw frame data
    int width;            // Frame width
    int height;           // Frame height
    int channels;         // Number of color channels
} VideoFrame;

// Video metadata structure
typedef struct {
    int total_frames;     // Total number of frames
    double duration;      // Total video duration
    int fps;              // Frames per second
    int width;            // Original video width
    int height;           // Original video height
} VideoMetadata;

// Video conversion result structure
typedef struct {
    char **ascii_frames;  // Array of ASCII frames
    int frame_count;      // Number of converted frames
} AsciiVideoResult;

// Function to convert video to ASCII
int convert_video_to_ascii(AppConfig *config);

// Function to extract frames from video
VideoFrame* extract_video_frames(const char *input_path, VideoMetadata *metadata);

// Function to free video frame memory
void free_video_frames(VideoFrame *frames, int frame_count);

// Function to save ASCII video to file
int save_ascii_video(const AsciiVideoResult *video_result, const char *output_path);

// Video processing options
typedef struct {
    int skip_frames;      // Number of frames to skip
    int max_frames;       // Maximum frames to process
    int resize_width;     // Resize video width
} VideoProcessingOptions;

#endif // VIDEO_CONVERTER_H
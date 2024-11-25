// video_player.h
#ifndef VIDEO_PLAYER_H
#define ASCII_PLAYER_H

#include "config.h"
#include "video_converter.h"

// Playback modes
typedef enum {
    PLAYBACK_NORMAL,
    PLAYBACK_LOOP,
    PLAYBACK_REVERSE
} PlaybackMode;

// Terminal display settings
typedef struct {
    int use_color;        // Enable color output
    int clear_screen;     // Clear screen between frames
    int show_progress;    // Show playback progress
} DisplaySettings;

// Function to play ASCII video in terminal
int play_ascii_video(AppConfig *config);

// Function to read ASCII video from file
AsciiVideoResult* load_ascii_video(const char *input_path);

// Function to free ASCII video memory
void free_ascii_video(AsciiVideoResult *video);

// Advanced playback controls
typedef struct {
    PlaybackMode mode;        // Playback mode
    double playback_speed;    // Speed multiplier
    int start_frame;          // Starting frame
    int end_frame;            // Ending frame
} PlaybackOptions;

// Terminal interaction functions
void setup_terminal();
void restore_terminal();
int handle_user_input(PlaybackOptions *options);

#endif // ASCII_PLAYER_H
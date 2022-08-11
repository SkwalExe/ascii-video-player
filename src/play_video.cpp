//
// Created by skwal on 8/10/22.
//

#include "play_video.h"
#include "utils.h"
#include <opencv2/opencv.hpp>
#include "terminal_size.h"
#include "colors.h"
using namespace std;
using namespace cv;

char ASCII_CHARS[] = "@#S%?+;:,. ";

int array_length(char const *array)
{
    int i = 0;
    while (array[i] != '\0')
        i++;
    return i;
}

void fit_image(Mat& image, int max_width, int max_height, float enlargement, bool stretch)
{
    if (stretch)
    {
        resize(image, image, Size(max_width, max_height), 0, 0, INTER_LINEAR);
        return;
    }
    double resize_factor_1 = (double)max_width / image.cols;
    double resize_factor_2 = (double)max_height / image.rows;
    double resize_factor = min(resize_factor_1, resize_factor_2);
    resize(image, image, Size(), resize_factor*enlargement, resize_factor, INTER_AREA);
}


void display_frame(Mat frame)
{
    static int chars_array_len = array_length(ASCII_CHARS) - 1;
    for (int x = 0; x < frame.rows; x++)
    {
        for (int y = 0; y < frame.cols; y++)
        {
              int pixel_gray_value = frame.at<uchar>(x, y);
              int char_index = chars_array_len * pixel_gray_value / 255;
              cout << ASCII_CHARS[char_index];
        }
        cout << "\n";
    }
    cout << flush;
}



void play_video(char *file, bool show_status, float enlargement, bool stretch)
{
    VideoCapture cap(file);
    
    if (!cap.isOpened())
    {
        clear();
        cout << RED << "[ x ] : Invalid video: " << file << RESET << endl;
        exit(1);
    }
    
    double frame_count = cap.get(CAP_PROP_FRAME_COUNT);
    double fps = cap.get(CAP_PROP_FPS);
    double duration = frame_count / fps;
    double frame_duration = duration*1000 / frame_count;
    int casted_frame_duration = (int)frame_duration;
    int width, height;
    get_terminal_size(width, height);
    if (show_status)
        height -= 6;
    
    clear();
    
    cout << PURPLE <<"Starting..." << endl;
    cout << PURPLE << "File: " << YELLOW << file << endl;
    cout << PURPLE << "Duration: "  << YELLOW << duration << " seconds / " << duration/60 << " minutes" << endl;
    cout << PURPLE << "FPS: " << YELLOW  << fps << endl;
    cout << PURPLE << "Frame count: " << YELLOW  << frame_count << endl;
    cout << PURPLE << "Terminal Width: " << YELLOW  << width << endl;
    cout << PURPLE << "Terminal Height: " << YELLOW  << height << endl;
    cout << PURPLE << "Video Width: " << YELLOW  << cap.get(CAP_PROP_FRAME_WIDTH) << endl;
    cout << PURPLE << "Video Height: " << YELLOW  << cap.get(CAP_PROP_FRAME_HEIGHT) << endl;
    cout << PURPLE << "Frame Duration: "  << YELLOW << frame_duration << " milliseconds" << endl;
    cout << PURPLE << "\nPress enter to start..." << RESET << endl;
    cin.get();
    
    
    sleep(1000);
    
    Mat frame;
    // for each frame
    for (int i = 0; i < frame_count; i++)
    {
        cap.read(frame);
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        fit_image(frame, width, height, enlargement, stretch);
        clear();
        if (show_status) {
            cout << i << "th frame / " << frame_count << "\n";
            cout << "progression : " << (i * 100 / frame_count) << "%" << "\n";
            cout << "frame duration : " << frame_duration << "\n";
            cout << "frame duration <casted> : " << (int) frame_duration << "\n";
            cout << "frame width : " << frame.cols << "\n";
            cout << "frame height : " << frame.rows << "\n";
        }
        display_frame(frame);
        sleep(casted_frame_duration);
        get_terminal_size(width, height);
        if (show_status)
            height -= 6;
    }
}
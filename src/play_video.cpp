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

char ASCII_CHARS[200] = "@#%?+;:,.";

void fit_image(Mat& image, int max_width, int max_height, bool stretch)
{
    if (stretch)
    {
        resize(image, image, Size(max_width, max_height), 0, 0, INTER_LINEAR);
        return;
    }
    
    max_width -= 1;
    max_height -= 1;
    
    resize(image, image, Size(), 2, 1, INTER_LINEAR);
    
    double resize_factor_1 = (double)max_width / image.cols;
    double resize_factor_2 = (double)max_height / image.rows;
    double resize_factor = min(resize_factor_1, resize_factor_2);
    
    resize(image, image, Size(), resize_factor, resize_factor, INTER_AREA);

}


void display_frame(Mat frame, bool inverse)
{
    static int chars_array_len = array_length(ASCII_CHARS) - 1;
    for (int x = 0; x < frame.rows; x++)
    {
        for (int y = 0; y < frame.cols; y++)
        {
              int pixel_gray_value = 255 - frame.at<uchar>(x, y);
              if (inverse)
                pixel_gray_value = 255 - pixel_gray_value;
              int char_index = chars_array_len * pixel_gray_value / 255;
              cout << ASCII_CHARS[char_index];
        }
        cout << "\n";
    }
    cout << flush;
}


void display_frame_with_colors(Mat frame, bool blocks, bool color_background)
{
    static int chars_array_len = array_length(ASCII_CHARS) - 1;
    resize(frame, frame, Size(), (blocks ? 0.5 : 1), 1, INTER_LINEAR);
    
    for (int x = 0; x < frame.rows; x++)
    {
        for (int y = 0; y < frame.cols; y++)
        {
              Vec3b pixel_color = frame.at<Vec3b>(x, y);
              
              if (blocks)
              {
                  cout << "\x1b[48;2;"
                       << (int)pixel_color[2] << ";" << (int)pixel_color[1] << ";" << (int)pixel_color[0]
                       << "m" << "  " << "\x1b[0m";
              }
              else {
                  int pixel_gray_value = (pixel_color[0] + pixel_color[1] + pixel_color[2]) / 3;
                  int char_index = chars_array_len * pixel_gray_value / 255;
    
                  cout << "\x1b[" << (color_background ? "48" : "38") << ";2;"
                       << (int) pixel_color[2] << ";" << (int) pixel_color[1] << ";" << (int) pixel_color[0]
                       << "m" << ASCII_CHARS[char_index] << "\x1b[0m";
              }
        }
        cout << "\n";
    }
    cout  << flush;
}


void play_video(Params params)
{
    if (array_length(ASCII_CHARS) + params.black_level > 200)
    {
        cout << RED << "[ x ] : Black level cannot be greater than " << (200 - array_length(ASCII_CHARS)) << RESET << endl;
        exit(1);
    }
    for (int i = 0; i < params.black_level; i++)
    {
        ASCII_CHARS[array_length(ASCII_CHARS)] = ' ';
    }
    
    VideoCapture cap(params.file);
    
    if (!cap.isOpened())
    {
        clear();
        cout << RED << "[ x ] : Invalid video: " << params.file << RESET << endl;
        exit(1);
    }
    
    double frame_count = cap.get(CAP_PROP_FRAME_COUNT);
    double fps = cap.get(CAP_PROP_FPS);
    double duration = frame_count / fps;
    double frame_duration = duration*1000 / frame_count;
    int casted_frame_duration = (int)frame_duration;
    int width, height;

    
    clear();
    
    cout << PURPLE <<"Starting..." << endl;
    cout << PURPLE << "File: " << YELLOW << params.file << endl;
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
    
    Mat frame;
    int precedent_width = 0;
    int precedent_height = 0;
    // for each frame
    for (int i = 0; i < frame_count; i++)
    {
        cap.read(frame);
        // double the frame width (1px = 2chars)
        //resize(frame, frame, Size(), 2, 1, INTER_LINEAR);

        if (!params.colors)
            cvtColor(frame, frame, COLOR_BGR2GRAY);
    
        get_terminal_size(width, height);
        if (params.show_status)
            height -= 5;
        fit_image(frame, width, height,  params.stretch);
        
        
        clear();
        if (params.show_status) {
            cout << RED << i << "th frame / " << frame_count << "\n";
            cout << PURPLE << "progression : " << YELLOW << (i * 100 / frame_count) << "%" << "\n";
            cout << PURPLE << "frame duration : " << YELLOW << frame_duration << "\n";
            cout << PURPLE << "frame/terminal width : " << YELLOW << frame.cols << " / " << width << "\n";
            cout << PURPLE << "frame/terminal height : " << YELLOW << frame.rows << " / " << height << "\n\n";
        }
        if (params.colors)
            display_frame_with_colors(frame, params.blocks, params.color_background);
        else
            display_frame(frame, params.inverse);
        
        sleep(casted_frame_duration);
 
       
    }
}
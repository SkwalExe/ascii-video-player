#include <iostream>
#include <fstream>
#include <cstring>
#include "play_video.h"
#include "utils.h"
#include "colors.h"
using namespace std;

typedef enum
{
  play,
  version,
  help
} command;

bool file_exists(char *fileName)
{
  ifstream infile(fileName);
  return infile.good();
}

int main(int argc, char *argv[])
{
  command cmd = play;
  char *file = nullptr;
  bool show_status = false;
  bool stretch = false;
  float enlargement = 1.8;

  for (int i = 1; i < argc; i++)
  {
    char *arg = argv[i];
    if (strcmp(arg, "--version") == 0 || strcmp(arg, "-v") == 0)
    {
      cmd = version;
    }
    else if (strcmp(arg, "--help") == 0 || strcmp(arg, "-h") == 0)
    {
      cmd = help;
    }
    else if (strcmp(arg, "--show-status") == 0 || strcmp(arg, "-s") == 0)
    {
      show_status = true;
    }
    else if (strcmp(arg, "--enlargement") == 0 || strcmp(arg, "-e") == 0)
    {
      enlargement = atof(argv[++i]);
      if (enlargement <= 0)
      {
        cout << RED << "[ x ] : Invalid enlargement factor: " << enlargement << RESET << endl;
        exit(1);
      }
      i++;
    }
    else if (strcmp(arg, "--stretch") == 0 || strcmp(arg, "-t") == 0)
    {
      stretch = true;
    }
    else if (file != nullptr)
    {
      std::cout << RED << "[ x ] : Invalid argument: " << arg << RESET << endl;
      cmd = help;
    }
    else
    {
      if (file_exists(arg))
      {
        file = arg;
      }
      else
      {
        std::cout << RED << "[ x ] : File not found: " << arg << RESET << endl;
        exit(1);
      }
    }
  }

  switch (cmd)
  {
  case version:
    std::cout << PURPLE << "ascii-video-player => " << YELLOW << "0.1.0" << std::endl;
    break;
  case help:
    cout << WHITE << "video-ascii-player" << RESET << endl;
    cout << PURPLE << "━━━━━━━━━━━━━━━━━" << RESET << endl;
    cout << WHITE << "Author: " << PURPLE << "SkwalExe" << RESET << endl;
    cout << WHITE << "Github: " << PURPLE << "https://github.com/SkwalExe/" << RESET << endl;
    cout << PURPLE << "━━━━━━━━━━━━━━━━━" << RESET << endl;
    cout << WHITE << "Play video files directly in your terminal" << RESET << endl;
    cout << PURPLE << "━━━━━━━━━━━━━━━━━" << RESET << endl;
    cout << WHITE << "Usage: " << PURPLE << "ascii-video-player " << YELLOW << "[options] <file>" << RESET << endl;
    cout << PURPLE << "\t-v, --version: " << YELLOW << "Display version" << RESET << endl;
    cout << PURPLE << "\t-h, --help: " << YELLOW << "Display this message" << RESET << endl;
    cout << PURPLE << "\t-s, --show-status: " << YELLOW << "Show player status" << RESET << endl;
    cout << PURPLE << "\t-e, --enlargement: " << YELLOW << "Set the enlargement factor [D: 1.8]" << RESET << endl;
    cout << PURPLE << "\t-t, --stretch: " << YELLOW << "Ignore the enlargement factor and stretch the video to fit the terminal" << RESET << endl;
    cout << PURPLE << "\t[file]: " << YELLOW << "The video file to play" << RESET << endl;
    cout << PURPLE << "━━━━━━━━━━━━━━━━━" << RESET << endl;
    cout << YELLOW << "What is the enlargement factor?" << RESET << endl;
    cout << PURPLE << "When you play a video with a regular video player, "
                      "every pixel is a square which has the same height and width. \n"
                      "But when you play it in your terminal, the pixels are not squares anymore but characters. \n"
                      "And depending on your terminal font, the characters may be thinner or smaller than regular pixels. \n"
                      "We use the enlargement factor to compensate this gap."
         << RESET << endl;
    cout << PURPLE << "━━━━━━━━━━━━━━━━━" << RESET << endl;
    break;
  case play:
    if (file == nullptr)
    {
      std::cout << RED << "[ x ] : No file specified" << RESET << std::endl;
      exit(1);
    }

    play_video(file, show_status, enlargement, stretch);
    clear();
    cout << YELLOW << "Tadaaaa!" << RESET << endl;
    break;
  }
  return 0;
}
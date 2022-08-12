#include <iostream>
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

int main(int argc, char *argv[])
{
  command cmd = play;
  Params params;

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
      params.show_status = true;
    }
    else if (strcmp(arg, "--stretch") == 0 || strcmp(arg, "-t") == 0)
    {
      params.stretch = true;
    }
    else if (strcmp(arg, "--colors") == 0 || strcmp(arg, "-c") == 0)
    {
      params.colors = true;
    }
    else if (strcmp(arg, "--blocks") == 0 || strcmp(arg, "-b") == 0)
    {
      params.blocks = true;
      params.colors = true;
    }
    else if (strcmp(arg, "--inverse") == 0 || strcmp(arg, "-i") == 0)
    {
      params.inverse = true;
    }
    else if (strcmp(arg, "--black-level") == 0 || strcmp("-l", arg) == 0)
    {
      params.black_level = atoi(argv[++i]);
    }
    else if (strcmp(arg, "--color-background") == 0 || strcmp(arg, "-g") == 0)
    {
      params.color_background = true;
    }
    else if (params.file != nullptr)
    {
      std::cout << RED << "[ x ] : Invalid argument: " << arg << RESET << endl;
      cmd = help;
    }
    else
    {
      if (!file_exists(arg))
      {
        std::cout << RED << "[ x ] : File not found: " << arg << RESET << endl;
        exit(1);
      }
      else
      {
        params.file = arg;
      }
    }
  }

  switch (cmd)
  {
  case version:
    std::cout << PURPLE << "ascii-video-player => " << YELLOW << "0.2.0" << std::endl;
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
    cout << PURPLE << "\t-t, --stretch: " << YELLOW << "Stretch the video to fit the terminal" << RESET << endl;
    cout << PURPLE << "\t-c, --colors: " << YELLOW << "Enable colors" << RESET << endl;
    cout << PURPLE << "\t-b, --blocks: " << YELLOW << "Use colored blocks instead of characters" << RESET << endl;
    cout << PURPLE << "\t-i, --inverse: " << YELLOW << "Inverse black & white" << RESET << endl;
    cout << PURPLE << "\t-l, --black-level: " << YELLOW << "The intensity of black pixels/chars [D: 2]" << RESET << endl;
    cout << PURPLE << "\t-g, --color-background: " << YELLOW << "Color the background instead of the character" << RESET << endl;
    cout << PURPLE << "\t[file]: " << YELLOW << "The video file to play" << RESET << endl;
    cout << PURPLE << "━━━━━━━━━━━━━━━━━" << RESET << endl;
    break;
  case play:
    if (params.file == nullptr)
    {
      std::cout << RED << "[ x ] : No file specified" << RESET << std::endl;
      exit(1);
    }

    play_video(params);
    clear();
    cout << YELLOW << "Tadaaaa!" << RESET << endl;
    break;
  }
  return 0;
}
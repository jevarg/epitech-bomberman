#ifndef _INTRO_HPP_
# define _INTRO_HPP_

extern "C"
{
# include <libavcodec/avcodec.h>
# include <libavformat/avformat.h>
# include <libswscale/swscale.h>
# include <unistd.h>
}

# include <SdlContext.hh>
# include <OpenGL.hh>
# include <Clock.hh>

# include "GameEngine.hpp"
# include "Input.hpp"

class Intro
{
public:
  Intro();
  ~Intro();

  bool initialize(const std::string &file);
  void play(t_gameinfo &gameInfo, gdl::SdlContext &win, gdl::AShader &shader);

private:
  bool nextFrame();
  void genTexture();
  bool update(gdl::SdlContext &win, gdl::Clock &clock, Input &input, Settings &set);
  void draw(gdl::AShader &shader, gdl::SdlContext &win, gdl::Clock clock, float x, float y);

  int		    _video;
  GLuint	    _texture;
  AVCodec           *_codec;
  AVFrame           *_frame, *_frameRGB;
  AVPacket          _packet;
  Square	    _square;
  AVDictionary      *_optionsDict;
  AVCodecContext    *_codecContext;
  AVFormatContext   *_formatContext;
  struct SwsContext *_sws;
};

#endif /* _INTRO_HPP_ */

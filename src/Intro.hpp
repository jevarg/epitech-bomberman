#ifndef _INTRO_HPP_
# define _INTRO_HPP_

# include <libavcodec/avcodec.h>
# include <libavformat/avformat.h>
# include <libswscale/swscale.h>
# include <SdlContext.hh>
# include <OpenGL.hh>

class Intro
{
public:
  Intro(gdl::SdlContext *win);
  ~Intro();

  bool initialize(const std::string &file);
  void play();

private:
  void nextFrame();

  gdl::SdlContext	*_win;

  int		_video;
  // const PixelFormat CONV_FORMAT = PIX_FMT_RGB24;
  // const char *fname = ".Ressource/Videos/intro.mp4";
  AVFormatContext *_formatContext;
  AVCodecContext  *_codecContext;
  AVCodec         *_codec;
  AVFrame         *_frame, *_frameRGB;
  AVPacket        _packet;
  AVDictionary    *_optionsDict;
  struct SwsContext *_sws_ctx;
  GLuint _texture_video;
};

#endif /* _INTRO_HPP_ */

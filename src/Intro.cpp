#include "Intro.hpp"

Intro::Intro(gdl::SdlContext *win)
{
  _formatContext = NULL;
  _codecContext = NULL;
  _codec = NULL;
  _frame = 0;
  _frameRGB = 0;
  _optionsDict = NULL;
  _sws_ctx = NULL;
}

Intro::~Intro()
{

}

bool Intro::initialize(const std::string &file)
{
  unsigned char *buff;
  int		 bytes;

  av_register_all();
  if (avformat_open_input(&_formatContext, file.c_str(), NULL, NULL) != 0
      || avformat_find_stream_info(_formatContext, NULL) < 0)
    return (false);
  for(unsigned char i = 0; i < _formatContext->nb_streams; ++i)
    if(_formatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
      {
	_video = i;
	break;
      }
  _codecContext = _formatContext->streams[_video]->codec;
  if ((_codec = avcodec_find_decoder(_codecContext->codec_id)) == NULL
      || avcodec_open2(_codecContext, _codec, &_optionsDict) < 0
      || (_frame = av_frame_alloc()) == NULL
      || (_frameRGB = av_frame_alloc()) == NULL
      || (bytes = avpicture_get_size(PIX_FMT_RGB24, _codecContext->width, _codecContext->height)) < 0
      || (buff = static_cast<unsigned char *>(av_malloc(bytes * sizeof(unsigned char)))) == NULL
      || (avpicture_fill((AVPicture *)_frameRGB, buff, PIX_FMT_RGB24,
			 _codecContext->width, _codecContext->height) < 0))
    return (false);
  return (true);
}

void Intro::play()
{

}

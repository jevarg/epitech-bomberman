#include "Intro.hpp"

Intro::Intro()
  : _square()
{
  _formatContext = NULL;
  _codecContext = NULL;
  _codec = NULL;
  _frame = 0;
  _frameRGB = 0;
  _optionsDict = NULL;
  _sws = NULL;
}

Intro::~Intro()
{

}

bool Intro::initialize(const std::string &file)
{
  unsigned char *buff;
  int		 bytes;

  av_register_all();
  if (avformat_open_input(&_formatContext, file.c_str(), NULL, NULL) < 0
      || avformat_find_stream_info(_formatContext, NULL) < 0)
    {
      std::cerr << "FAILED" << std::endl;
      return (false);
    }
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
  genTexture();
  _sws = sws_getCachedContext(_sws, _codecContext->width, _codecContext->height,
  				  _codecContext->pix_fmt, _codecContext->width,
  				  _codecContext->height, PIX_FMT_RGB24,
  				  SWS_BICUBIC, NULL, NULL, NULL);
  if (_sws == NULL)
    return (false);
  _square.setScale(1, -1);
  _square.setPos(0, 900);
  return (true);
}

void Intro::genTexture()
{
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _codecContext->width, _codecContext->height,
	       0, GL_RGB, GL_UNSIGNED_BYTE, _frameRGB->data[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

bool Intro::nextFrame()
{
  int frameEnd = 0;

  while (av_read_frame(_formatContext, &_packet) >= 0)
    {
      if (_packet.stream_index == _video)
	{
	  avcodec_decode_video2(_codecContext, _frame, &frameEnd, &_packet);
	  if (frameEnd)
	    {
	      sws_scale (_sws, (uint8_t const * const *)_frame->data,
			 _frame->linesize, 0, _codecContext->height, _frameRGB->data,
			 _frameRGB->linesize);
	      glBindTexture( GL_TEXTURE_2D, _texture );
	      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	      glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, _codecContext->width,
			      _codecContext->height, GL_RGB, GL_UNSIGNED_BYTE, _frameRGB->data[0]);
	      return (true);
	    }
	}
      av_free_packet(&_packet);
    }
  return (false);
}

bool Intro::update(gdl::SdlContext &win, gdl::Clock &clock, Input &input, Settings &set)
{
  input.getInput(set);
  usleep(30.0 * 1000);
  if (!nextFrame() || input.isPressed(SDLK_SPACE))
    return (false);
  win.updateClock(clock);
  return (true);
}

void Intro::draw(gdl::AShader &shader, gdl::SdlContext &win, gdl::Clock clock, float x, float y)
{
  shader.bind();
  shader.setUniform("projection", glm::ortho(0.0f, x, y, 0.0f, -1.0f, 1.0f));
  shader.setUniform("view", glm::mat4(1));
  shader.setUniform("winX", x);
  shader.setUniform("winY", y);
  glDisable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT);
  glBindTexture(GL_TEXTURE_2D, _texture);
  _square.draw(shader, clock);
  glEnable(GL_DEPTH_TEST);
  win.flush();
}

void Intro::play(t_gameinfo &gameInfo, gdl::SdlContext &win, gdl::AShader &shader)
{
  float x = gameInfo.set->getVar(W_WIDTH), y = gameInfo.set->getVar(W_HEIGHT);

  _square.setSize(x, y);
  _square.fillGeometry();
  while (update(win, *gameInfo.clock, *gameInfo.input, *gameInfo.set))
    draw(shader, win, *gameInfo.clock, x, y);
}

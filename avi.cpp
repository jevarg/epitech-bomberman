
  #include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
#include <unistd.h>
#include <SDL.h>
#include <GL/gl.h>

int fullscreen = 1, videoStream = -1, frameFinished=0;
const PixelFormat CONV_FORMAT = PIX_FMT_RGB24;
const char *fname = "./Ressources/Videos/intro.mp4";
AVFormatContext *pFormatCtx = NULL;
AVCodecContext  *pCodecCtx = NULL;
AVCodec         *pCodec = NULL;
AVFrame         *pFrame = 0, *pFrameRGB = 0;
AVPacket        packet;
AVDictionary    *optionsDict = NULL;
struct SwsContext *sws_ctx = NULL;
GLuint texture_video;

void av_init();
void next_frame();

int main(int argc, const char **argv) {
  SDL_Event event;

  av_init();

  uint16_t width = fullscreen ? 1600 : pCodecCtx->width;
  uint16_t height = fullscreen ? 900 : pCodecCtx->height;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  SDL_SetVideoMode(width, height, 32, SDL_OPENGL);

  glEnable(GL_TEXTURE_2D);
  glClearColor(0.0f, 0.4f, 0.4f, 0.0f);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glShadeModel(GL_SMOOTH);
  glGenTextures(1, &texture_video);
  glBindTexture(GL_TEXTURE_2D, texture_video);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pCodecCtx->width, pCodecCtx->height, 0, GL_RGB, GL_UNSIGNED_BYTE, pFrameRGB->data[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  sws_ctx = sws_getCachedContext(sws_ctx, pCodecCtx->width, pCodecCtx->height,
				 pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, CONV_FORMAT,
				 SWS_BICUBIC, NULL, NULL, NULL);

  while (1) {

    while(SDL_PollEvent(&event))
      {
	switch(event.type) {
	case SDL_QUIT:
	  SDL_Quit();
	  exit(0);
	  break;
	case SDL_KEYDOWN:
	  if (event.key.keysym.sym == SDLK_ESCAPE) {
	    SDL_Quit();
	    exit(0);
	  }
	  break;
	default:
	  break;
        }
      }

    next_frame();

    glClear(GL_COLOR_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture_video);
    glScalef(1.0f, -1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    glScalef(1.0f, -1.0f, 1.0f);

    SDL_GL_SwapBuffers();
    usleep(20000);
  }
  return 0;
}

void next_frame()
{
  while( true )
    {
      if( av_read_frame(pFormatCtx, &packet) >= 0 )
        {
	  if( packet.stream_index == videoStream )
            {
	      avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);
	      if(frameFinished)
                {
		  sws_scale (sws_ctx, (uint8_t const * const *)pFrame->data,
			     pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
			     pFrameRGB->linesize);
		  glBindTexture( GL_TEXTURE_2D, texture_video );
		  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, pCodecCtx->width,
				  pCodecCtx->height, GL_RGB, GL_UNSIGNED_BYTE, pFrameRGB->data[0]);
		  break;
                }
            }
	  av_free_packet(&packet);
        }
      else
        {
	  av_seek_frame(pFormatCtx, videoStream, 0,  AVSEEK_FLAG_FRAME);
        }
    }
}

void av_init() {
  av_register_all();
  avformat_open_input(&pFormatCtx, fname, NULL, NULL);
  avformat_find_stream_info(pFormatCtx, NULL);
  for(uint8_t i = 0; i < pFormatCtx->nb_streams; i++)
    if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO) {
      videoStream=i;
      break;
    }
  pCodecCtx = pFormatCtx->streams[videoStream]->codec;
  pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
  avcodec_open2(pCodecCtx, pCodec, &optionsDict);
  pFrame = av_frame_alloc();
  pFrameRGB = av_frame_alloc();
  int bytes = avpicture_get_size(CONV_FORMAT, pCodecCtx->width, pCodecCtx->height);
  uint8_t *video_buffer = (uint8_t*)av_malloc(bytes * sizeof(uint8_t));
  avpicture_fill((AVPicture *)pFrameRGB, video_buffer, CONV_FORMAT, pCodecCtx->width, pCodecCtx->height);
}

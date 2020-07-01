#ifndef __LOG_H__
#define __LOG_H__

#define LOG( text , info ) (  LogWrite(__FILE__ , __LINE__ , __func__ , text , info ) )

typedef enum{ OK , ERROR }MsgType;

void LogWrite(char *_file , int _line ,const char *_func , char *_txt , MsgType _msgType);

#endif /* __LOG_H__ */

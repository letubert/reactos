#include <msvcrti.h>


int _utime(const char* filename, struct _utimbuf* buf)
{
  int fn;
  int ret;
  
  fn = _open(filename, _O_RDWR);
  if (fn == -1)
    {
      __set_errno(EBADF);
      return -1;
    }
  ret = _futime(fn,buf);
  if (_close(fn) < 0)
    return -1;
  return ret;
}

int _wutime(const wchar_t* filename, struct _utimbuf* buf)
{
  int fn;
  int ret;
  
  fn = _wopen(filename, _O_RDWR);
  if (fn == -1)
    {
      __set_errno(EBADF);
      return -1;
    }
  ret = _futime(fn,buf);
  if (_close(fn) < 0)
    return -1;
  return ret;
}

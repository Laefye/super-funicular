#ifndef API_H
#define API_H
#ifdef EXPORT
#define API __declspec(dllexport) 
#else
#define API
#endif
#endif

#ifndef _2_H_
#define _2_H_

#ifdef __cplusplus
extern "C" //��֪����������void f()������C���������
#endif
void f();

#ifdef __cplusplus
extern "C" {
#endif
void f1();
void f2();
void f3();
#ifdef __cplusplus
}
#endif

#endif
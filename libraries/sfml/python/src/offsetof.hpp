#ifndef __OFFSETOF_H
#define __OFFSETOF_H

#undef offsetof
#define offsetof(TYPE, MEMBER) (reinterpret_cast <size_t> \
	(&reinterpret_cast <char &>(static_cast <TYPE *> (0)->MEMBER)))

#endif

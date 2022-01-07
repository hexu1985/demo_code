// -*- C++ -*-
// HeXu's
// 2013 Oct

#ifndef STATIC_ASSERT_H
#define STATIC_ASSERT_H

#define JOIN(X, Y) DO_JOIN(X, Y)
#define DO_JOIN(X, Y) DO_JOIN2(X, Y)
#define DO_JOIN2(X, Y) X##Y

#define STATIC_ASSERT(condition, ...) \
	enum { JOIN(static_assert_enum_, __LINE__) \
		= 1/(condition) }

#endif // STATIC_ASSERT_H


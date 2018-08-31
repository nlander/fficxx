#ifdef __cplusplus
extern "C" {
#endif

#include "cpp_magic.h"

#define VARGS(...) __VA_ARGS__

#define TAIL(x,...) __VA_ARGS__

#define UNPAREN(x) VARGS x

#define GETTYPE(X) FIRST X
#define GETVAR(X) SECOND X

#define GETTYPES(x) MAP(GETTYPE,COMMA,UNPAREN(x))
#define GETVARS(x) MAP(GETVAR,COMMA,UNPAREN(x))

#define Function_new_decl(NAME,R,ATYPS)                         \
    void* Function_new_ ## NAME ( R (*fp) ( GETTYPES(ATYPS) ));

#define Function_call_decl(NAME,R,ATYPS)                                \
    R Function_call_ ## NAME ( REMOVE_TRAILING_COMMAS( void*, GETTYPES(ATYPS) ) );

#define Function_delete_decl(NAME,R,ATYPS)           \
    void Function_delete_ ## NAME ( void*  );

#define Function_new_inst(NAME,R,ATYPS)                                \
    inline void* Function_new_ ## NAME ( R (*fp)( GETTYPES(ATYPS) ) )   \
    {                                                                   \
        std::function< R ( GETTYPES(ATYPS) )>* p = new std::function< R ( GETTYPES(ATYPS) ) >(fp); \
        return static_cast<void*>(p);                                   \
    }                                                                   \
    auto a_Function_new_ ## NAME = Function_new_ ## NAME;


#define Function_call_inst(NAME,R,ATYPS)        \
    inline R Function_call_ ## NAME ( REMOVE_TRAILING_COMMAS( void* op,  UNPAREN(ATYPS) ) ) \
    {                                                                   \
        std::function< R ( GETTYPES(ATYPS) )>* p = static_cast< std::function< R ( GETTYPES(ATYPS) )>* >(op); \
        return (*p) ( GETVARS(ATYPS) );                              \
    }                                                                   \
    auto a_Function_call_ ## NAME = Function_call_ ## NAME;

#define Function_delete_inst(NAME,R,ATYPS)             \
    inline void Function_delete_ ## NAME ( void* op )   \
    {                                                                   \
        std::function< R ( GETTYPES(ATYPS) ) >* p = static_cast< std::function< R ( GETTYPES(ATYPS) ) >* >(op); \
        delete p;                                                       \
    }                                                                   \
    auto a_Function_delete_ ## NAME = Function_delete_ ## NAME;

/*
#define Function_new_decl(NAME,R,ATYPS)\
  void* Function_new_ ## NAME ( R (*fp) ( UNPAREN(ATYPS) ) );

#define Function_call_decl(NAME,R,ATYPS)\
  R Function_call_ ## NAME ( UNPAREN(ATYPS) );

#define Function_delete_decl(NAME)\
  void Function_delete_ ## NAME ( void* );

#define Function_new_inst(NAME,R,ATYPS)                     \
    inline void* Function_new_ ## NAME ( R (*fp)( UNPAREN(ATYPS) ) ) \
  {\
      std::function< R ( UNPAREN(ATYPS) )>* p = new std::function< R ( UNPAREN(ATYPS) ) >(fp); \
    return static_cast<void*>(p);\
  }\
  auto a_Function_new_ ## NAME = Function_new_ ## NAME;


#define Function_call_inst(NAME,R,ATYPS,AVARS)        \
  inline R Function_call_ ## NAME ( UNPAREN(ATYPS) ) \
  {\
      std::function< R (TAIL ATYPS) >* p = static_cast< std::function< R (TAIL ATYPS) >* >(op); \
    return (*p) AVARS;                                 \
  }\
  auto a_Function_call_ ## NAME = Function_call_ ## NAME;

#define Function_delete_inst(NAME,R,ATYPS)        \
  inline void Function_delete_ ## NAME ( void* op ) \
  {\
      std::function< R (TAIL ATYPS) >* p = static_cast< std::function< R (TAIL ATYPS) >* >(op); \
    delete p;\
  }\
  auto a_Function_delete_ ## NAME = Function_delete_ ## NAME;
*/

#ifdef __cplusplus
}
#endif

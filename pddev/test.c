#include "m_pd.h"

static t_class *test_class;

typedef struct _test
{
    t_object x_obj;
} t_test;

void  *test_new(void){
	t_test *x = (t_test *)pd_new(test_class);
	post("hello");
	return (void *)x;
}

void test_setup(void){
	test_class = class_new(gensym("test"),
	(t_newmethod)test_new, 
	0, 
	sizeof(t_test), CLASS_DEFAULT, 
	0);
}

// mycpppymodule.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <Python.h>
#include <iostream>

#include "mycpppymodule.h"

// Copy & Pasted from...
// http://www.tutorialspoint.com/python/python_further_extensions.htm
// https://docs.python.org/2/extending/extending.html
// https://github.com/sushantkhurana/Python-C-Extension/blob/master/helloWorld.cpp

static PyObject *my_callback = nullptr;

static PyObject *my_set_callback(PyObject *self, PyObject *args)
{
	PyObject *result = nullptr;
	PyObject *temp = nullptr;

	if (PyArg_ParseTuple(args, "O:set_callback", &temp))
	{
		if (!PyCallable_Check(temp))
		{
			PyErr_SetString(PyExc_TypeError, "parameter must be callable");
			return nullptr;
		}

		Py_XINCREF(temp);         /* Add a reference to new callback */
		Py_XDECREF(my_callback);  /* Dispose of previous callback */
		my_callback = temp;       /* Remember new callback */
		/* Boilerplate to return "None" */
		Py_INCREF(Py_None);
		result = Py_None;
	}

	return result;
}

static PyObject* my_testcallback(PyObject* self)
{
	int arg = 1234;
	PyObject *arglist = nullptr;
	PyObject *result = nullptr;
	
	/* Time to call the callback */
	arglist = Py_BuildValue("(i)", arg);
	result = PyObject_CallObject(my_callback, arglist);
	Py_DECREF(arglist);
	
	if (result == NULL)
		return NULL;
	Py_DECREF(result);

	return result;	
}

static PyObject* mycpppymodule_callback(PyObject* self, PyObject* arg)
{
	PyObject* result = PyObject_CallObject(arg, nullptr);

	if (result != NULL)
		Py_DECREF(result);

	return result;
}

static PyObject *mycpppymodule_add(PyObject *self, PyObject *args)
{
	int a = 0;
	int b = 0;

	if (!PyArg_ParseTuple(args, "ii", &a, &b))
	{
		return NULL;
	}

	return Py_BuildValue("i", a + b);
}

static PyObject *add_subtract(PyObject *self, PyObject *args)
{
	int a = 0;
	int b = 0;

	if (!PyArg_ParseTuple(args, "ii", &a, &b)) 
	{
		return NULL;
	}

	return Py_BuildValue("ii", a + b, a - b);
}

static PyObject* mycpppymodule_helloworld(PyObject* self, PyObject *args)
{
	std::string str = "hello, ";

	char* name = nullptr;

	if (!PyArg_ParseTuple(args, "s", &name))
	{
		return NULL;
	}

	str.append(name);
	return Py_BuildValue("s", str.c_str());
}


static char mycpppymodule_docs[] = "helloworld(name): say hello to name!!\n";

static PyMethodDef mycpppymodule_funcs[] =
{
	{ "helloworld", (PyCFunction)mycpppymodule_helloworld, METH_VARARGS, mycpppymodule_docs },
	{ "add_subtract", add_subtract, METH_VARARGS, "receives and returns typle" },
	{ "add", mycpppymodule_add, METH_VARARGS, "add only" },
	{ "my_set_callback", my_set_callback, METH_VARARGS, "set callback" },
	{ "my_testcallback", (PyCFunction)my_testcallback, METH_NOARGS, "call registered callback" },
	{ NULL, NULL, 0, NULL }
};

extern "C"
{
	MYCPPPYMODULE_API void initmycpppymodule(void);
}

MYCPPPYMODULE_API void initmycpppymodule(void)
{
	auto pyObj = Py_InitModule3(
		"mycpppymodule",
		mycpppymodule_funcs,
		"!!!docstring!!! Extension module example!");
}

/*
// This is an example of an exported variable
MYCPPPYMODULE_API int nmycpppymodule=0;

// This is an example of an exported function.
MYCPPPYMODULE_API int fnmycpppymodule(void)
{
return 42;
}

// This is the constructor of a class that has been exported.
// see mycpppymodule.h for the class definition
Cmycpppymodule::Cmycpppymodule()
{
return;
}
*/
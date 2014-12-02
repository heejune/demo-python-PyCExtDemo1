
import mycpppymodule as mycppmodule

# helloworld
print mycppmodule.helloworld(u"your name")

# add_subtract
plus,minus = mycppmodule.add_subtract(10, 5)

def python_called_from_native(val):
    print('Python called from native')
    print val
    return 4321

mycppmodule.my_set_callback(python_called_from_native)

retfromcallback = mycppmodule.my_testcallback()

print retfromcallback

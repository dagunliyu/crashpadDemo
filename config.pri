
TEST_CRASHPAD_DIR = \
    D:\Projects\Proj_Basic_proj\build_cp\cp_cxx14\crashpad
TEST_CRASHPAD_LIB_DIR =  \
    D:\Projects\Proj_Basic_proj\build_cp\cp_cxx14\crashpad\x64\release\obj

#CONFIG += static
#
#macx {
#    CONFIG += c++11
#    LIBS += -lcrypto
#}
#
## test config
## TODO actually, I shoud check it better
#LIST = thread exceptions rtti stl
#for(f, LIST) {
#    !CONFIG($$f) {
#        warning("Add '$$f' to CONFIG, or you will find yourself in 'funny' problems.")
#    }
#}
#
## define breakpad server    SOCORRO / CALIPER
#DEFINES += CALIPER

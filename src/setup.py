from distutils.core import setup, Extension
setup(name = 'mjsmodule', version = '1.0.0',  \
#  ext_modules = [Extension('mjsmodule', ['mjsso.c'])])
   ext_modules = [Extension('mjsmodule', ['mjsso.c','client.c','player.c'], extra_compile_args=['-Wno-unused-variable'] )]) 

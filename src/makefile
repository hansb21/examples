#
# MIT License
#
# Copyright(c) 2011-2020 The Maintainers of Nanvix
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

# Builds everything.
all: all-hello all-thread all-globalval
# Cleans up build objects.
clean: clean-hello clean-thread
# Cleans up everything.
distclean: distclean-hello disclean-`thread
#===============================================================================
# Hello World
#===============================================================================
# Builds the app.
all-hello:
	$(MAKE) -C hello all
# Cleans up build objects.
clean-hello:
	$(MAKE) -C hello clean
# Cleans up everything.
distclean-hello:
	$(MAKE) -C hello distclean
#===============================================================================
# thread
#===============================================================================
# Builds the app.
all-thread:
	$(MAKE) -C thread all
# Cleans up build objects.
clean-thread:
	$(MAKE) -C thread clean
# Cleans up everything.
distclean-thread:
	$(MAKE) -C thread distclean
#===============================================================================
# Global Variable
#===============================================================================
# Builds the app.
all-globalval:
	$(MAKE) -C globalval all
# Cleans up build objects.
clean-globalval:
	$(MAKE) -C globalval clean
# Cleans up everything.
distclean-globalval:
	$(MAKE) -C globalval distclean
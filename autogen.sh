#!/bin/sh

intltoolize --automake \
&& autoreconf --install --verbose

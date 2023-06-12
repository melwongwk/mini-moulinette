#!/bin/sh

python3 -m pip install --upgrade pip setuptools
pip3 install norminette
ln -s /workspaces/mini-moulinette ~/mini-moulinette
git clone https://github.com/cacharle/c_formatter_42 ~/c_formatter_42
pip3 install -e ~/c_formatter_42

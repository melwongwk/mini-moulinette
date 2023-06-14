#!/bin/sh

python3 -m pip install --upgrade pip setuptools
pip3 install norminette
git clone https://github.com/cacharle/c_formatter_42 ~/c_formatter_42
pip3 install -e ~/c_formatter_42
ln -s /workspaces/mini-moulinette ~/mini-moulinette
echo "alias mini='~/mini-moulinette/mini-moul.sh'" >> ~/.bashrc && source ~/.bashrc

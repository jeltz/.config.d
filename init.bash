#!/usr/bin/env bash

# Directory of this script
CONFIG_ROOT=$(cd `dirname $0` && pwd)

# Store location of config root
echo "CONFIG_ROOT='${CONFIG_ROOT}'" > ${HOME}/.config_root

# Determine OS
source ${CONFIG_ROOT}/determine_os

# Handle Windows
function _link() {
  if $OS_WINDOWS ; then
    cp -a $1 $2
    echo "Copied $1 -> $2"
  else
    if $OS_OSX ; then
      ln -sfh $1 $2
    else
      ln -sf $1 $2
    fi
    echo "Linked $1 -> $2"
  fi
}

# Link
_link ${CONFIG_ROOT}/profile/.bash_profile ${HOME}/.bash_profile
_link ${CONFIG_ROOT}/vim/.vimrc ${HOME}/.vimrc
_link ${CONFIG_ROOT}/tmux/.tmux.conf ${HOME}/.tmux.conf
if $OS_WINDOWS ; then
  _link ${CONFIG_ROOT}/git/windows/.gitconfig ${HOME}/.gitconfig
  [ -d ${HOME}/vimfiles ] && rm -rf ${HOME}/vimfiles
  _link ${CONFIG_ROOT}/vim/.vim ${HOME}/vimfiles
else
  _link ${CONFIG_ROOT}/git/.gitconfig ${HOME}/.gitconfig
  _link ${CONFIG_ROOT}/vim/.vim ${HOME}/.vim
fi
nbhome=${HOME}/.newsbeuter
[ ! -d ${nbhome} ] && mkdir ${nbhome}
[ ! -f ${nbhome}/config ] && _link ${CONFIG_ROOT}/newsbeuter/config ${nbhome}/config

FROM ubuntu:latest
RUN apt-get update && apt-get install -y \
    g++ \
    git \
    make \
    qt5-default \
    openssh-client \
    openssh-server \
    vim
    
# Reference GitHub Oauth token inorder to perform clone.
# TODO: Use a GitHub deploy key instead.
ENV APP_HOME=/home/PathFinder

# Checkout project from git repo.
RUN git clone https://github.com/robinschiro/PathFinder.git \
    ${APP_HOME}
    
# Make the 'driver' executable.    
#RUN qmake -r ${APP_HOME}

# Add psynth.sh to PATH
#ENV PATH=$PATH:${PSYNTH_SRC}

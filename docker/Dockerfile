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
    
ARG boost_version=1.62.0
ARG boost_dir=boost_1_62_0
ENV boost_version ${boost_version}

RUN wget http://downloads.sourceforge.net/project/boost/boost/${boost_version}/${boost_dir}.tar.gz \
    && tar xfz ${boost_dir}.tar.gz \
    && rm ${boost_dir}.tar.gz \
    && cd ${boost_dir} \
    && ./bootstrap.sh \
    && ./b2 --without-python --prefix=/usr -j 4 link=shared runtime-link=shared install \
    && cd .. && rm -rf ${boost_dir} && ldconfig

# Make the 'PathFinder' executable.
RUN cd ${APP_HOME} \
    && qmake \
    && make

# Add psynth.sh to PATH
ENV PATH=$PATH:${APP_HOME}

pipeline {
    agent {
        docker {
            image 'archlinux'
            args '-v ${WORKSPACE}/build:${WORKSPACE}/build'
        }
    }
    stages{
        stage('setup'){
            parallel{
                stage('install dependencies'){
                    steps{
                        sh 'pacman -Sy --noconfirm cmake base-devel doxygen graphviz git glew sfml glm stb'
                    }
                }
                stage('fetch submodules'){
                    steps{
                        sh 'git submodule update --recursive --remote'
                    }
                }
            }
        }
        stage('Configure CMake project'){
            steps{
                sh 'cmake -B build/ -S src'
            }
        }
        stage('Compile'){
            steps{
                sh 'cmake --build build/ -j'
            }
        }
    }
}

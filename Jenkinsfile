pipeline {
    agent {
        docker {
            image 'archlinux'
            args '-v ${WORKSPACE}/build:${WORKSPACE}/build'
        }
    }
    stages{
        stage('Install dempendencies'){
            steps{
                sh 'pacman -Sy --noconfirm cmake base-devel doxygen graphviz git glew sfml glm stb'
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

pipeline {
    agent {
        docker {
            image 'archlinux'
            args '-v /var/jenkins_home/workspace/psk-proj-podstawy-grafiki-komputerowej-2/build:/var/jenkins_home/workspace/psk-proj-podstawy-grafiki-komputerowej-2/build'
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
                sh 'cmake -B build/'
            }
        }
        stage('Compile'){
            steps{
                sh 'cmake --build build/ -j'
            }
        }
    }
}

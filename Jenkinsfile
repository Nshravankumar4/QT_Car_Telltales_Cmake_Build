pipeline {
    agent any
    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/Nshravankumar4/QT_Car_Telltales_Cmake_Build.git'
            }
        }
        stage('Configure') {
            steps {
                bat '"C:\\Qt\\5.15.2\\msvc2019_64\\bin\\qtenv2.bat" && cmake -S . -B build -DCMAKE_BUILD_TYPE=Release'
            }
        }
        stage('Build') {
            steps {
                bat 'cmake --build build --config Release'
            }
        }
        stage('Run') {
            steps {
                bat 'build\\Release\\QtTelltaleProject.exe'
            }
        }
    }
}

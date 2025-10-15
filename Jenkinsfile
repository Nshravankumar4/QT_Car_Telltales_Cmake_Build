pipeline {
    agent any
    stages {
        stage('Checkout') {
            steps {
                git 'https://github.com/Nshravankumar4/QT_Car_Telltales_Cmake_Build.git'
            }
        }
        stage('Configure') {
            steps {
                bat 'call "C:\\Qt\\5.15.2\\msvc2019_64\\bin\\qtenv2.bat"'
                bat 'cmake -S %WORKSPACE% -B %WORKSPACE%\\build -DCMAKE_BUILD_TYPE=Release'
            }
        }
        stage('Build') {
            steps {
                bat 'cmake --build %WORKSPACE%\\build --config Release'
            }
        }
        stage('Archive') {
            steps {
                archiveArtifacts artifacts: 'build/**', fingerprint: true
            }
        }
    }
}

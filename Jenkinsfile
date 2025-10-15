pipeline {
    agent any

    environment {
        QT_PATH = "C:\\Qt\\5.15.2\\msvc2019_64"  // Path to your Qt installation
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Configure') {
            steps {
                bat "\"${env.QT_PATH}\\bin\\qtenv2.bat\" && cmake -S . -B build -DCMAKE_BUILD_TYPE=Release"
            }
        }

        stage('Build') {
            steps {
                bat "cmake --build build --config Release"
            }
        }

        stage('Run') {
            steps {
                bat "build\\Release\\QtTelltaleProject.exe"
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: 'build/**/*', allowEmptyArchive: true
        }
    }
}

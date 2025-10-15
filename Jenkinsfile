pipeline {
    agent any

    environment {
        QT_DIR = 'C:\\Qt\\5.15.2\\msvc2019_64'
        VS_DIR = 'C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Professional'
        BUILD_DIR = 'build'
    }

    stages {
        stage('Checkout SCM') {
            steps {
                echo "Checking out code from main branch"
                checkout scm
            }
        }

        stage('Setup Repository') {
            steps {
                echo "Running setup repository batch script..."
                // Call batch file with main branch argument
                bat 'call "%WORKSPACE%\\Scripts\\Setup_Repo.bat" main'
            }
        }

        stage('Setup Environment') {
            steps {
                echo "Setting up Qt and Visual Studio environment..."
                bat """
                    call "%QT_DIR%\\bin\\qtenv2.bat"
                    call "%VS_DIR%\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
                """
            }
        }

        stage('Clean') {
            steps {
                echo "Cleaning previous build files..."
                bat """
                    rmdir /S /Q "%WORKSPACE%\\%BUILD_DIR%" || echo Directory not found
                    del "%WORKSPACE%\\CMakeCache.txt" || echo No cache file found
                """
            }
        }

        stage('CMake Configure') {
            steps {
                echo "Configuring CMake project..."
                bat """
                    cmake -S "%WORKSPACE%" -B "%WORKSPACE%\\%BUILD_DIR%" -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="%QT_DIR%\\lib\\cmake"
                """
            }
        }

        stage('CMake Build') {
            steps {
                echo "Building project..."
                bat """
                    cmake --build "%WORKSPACE%\\%BUILD_DIR%" --config Release
                """
            }
        }

        stage('Run') {
            steps {
                echo "Running executable..."
                bat """
                    "%WORKSPACE%\\%BUILD_DIR%\\Release\\QtTelltaleProject.exe"
                """
            }
        }

        stage('Archive Artifacts') {
            steps {
                echo "Archiving built executable..."
                archiveArtifacts artifacts: '%WORKSPACE%\\%BUILD_DIR%\\Release\\QtTelltaleProject.exe', fingerprint: true
            }
        }
    }

    post {
        success {
            echo "Build completed successfully!"
        }
        failure {
            echo "Build failed. Check logs above for errors."
        }
    }
}

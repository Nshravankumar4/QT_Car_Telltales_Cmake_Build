pipeline {
    agent any

    environment {
        QT_DIR = 'C:\\Qt\\5.15.2\\msvc2019_64'
        VS_DIR = 'C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Professional'
        BUILD_DIR = 'build'
        BRANCH_NAME = 'main'
        PATH = 'C:\\Windows\\System32;C:\\Windows' // Minimal PATH to avoid issues
    }

    stages {
        stage('Checkout SCM') {
            steps {
                echo "Checking out code from main branch..."
                checkout scm
            }
        }

        stage('Setup Repository') {
            steps {
                echo "Running setup repository batch script..."
                bat """
                    cd /d "%WORKSPACE%\\Scripts"
                    call Setup_Repo.bat "%BRANCH_NAME%"
                """
            }
        }

        stage('Setup Environment') {
            steps {
                echo "Setting up Qt and Visual Studio environment..."
                bat """
                    call "%QT_DIR%\\bin\\qtenv2.bat"
                    call "%VS_DIR%\\VC\\Auxiliary\\Build\\vcvarsall.bat" x64
                    cd /d %WORKSPACE%
                """
            }
        }

        stage('Clean') {
            steps {
                echo "Cleaning previous build..."
                bat """
                    cd /d %WORKSPACE%
                    rmdir /S /Q %BUILD_DIR% || echo Directory not found
                    del CMakeCache.txt || echo No cache file found
                """
            }
        }

        stage('CMake Configure') {
            steps {
                echo "Configuring CMake..."
                bat """
                    cd /d %WORKSPACE%
                    cmake -S . -B %BUILD_DIR% -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="%QT_DIR%\\lib\\cmake"
                """
            }
        }

        stage('CMake Build') {
            steps {
                echo "Building project..."
                bat """
                    cd /d %WORKSPACE%
                    cmake --build %BUILD_DIR% --config Release
                """
            }
        }

        stage('Run Executable') {
            steps {
                echo "Running executable..."
                bat """
                    cd /d %WORKSPACE%
                    %BUILD_DIR%\\Release\\QtTelltaleProject.exe
                """
            }
        }

        stage('Archive Artifacts') {
            steps {
                echo "Archiving executable..."
                archiveArtifacts artifacts: '%BUILD_DIR%\\Release\\QtTelltaleProject.exe', fingerprint: true
            }
        }
    }

    post {
        success {
            echo 'Build succeeded!'
        }
        failure {
            echo 'Build failed. Check logs above for errors.'
        }
    }
}

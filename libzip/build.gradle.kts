plugins {
    id("com.android.library")
    id("maven-publish")
}

group = "com.aliucord"

android {
    compileSdk = 30

    defaultConfig {
        minSdk = 21
        targetSdk = 29
    }

    buildTypes {
        release {
            isMinifyEnabled = false
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
        }
    }
}

afterEvaluate {
    publishing {
        publications {
            register(project.name, MavenPublication::class.java) {
                group = "com.github.Aliucord"

                from(components["release"])
            }
        }
    }
}

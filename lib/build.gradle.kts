plugins {
    alias(libs.plugins.android.library)
    alias(libs.plugins.kotlin.android)
    alias(libs.plugins.kotlin.serialization)
    `maven-publish`
}

group = "com.kyant.tag"
version = "2023.8.2"

android {
    namespace = "com.kyant.tag"
    compileSdk = 34
    ndkVersion = "25.1.8937393"

    defaultConfig {
        minSdk = 21
        consumerProguardFiles("consumer-rules.pro")
        ndk {
            abiFilters += arrayOf("arm64-v8a", "armeabi-v7a", "x86_64", "x86")
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
    externalNativeBuild {
        cmake {
            path("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
    kotlin {
        jvmToolchain(17)
    }
    lint {
        checkReleaseBuilds = false
    }
}

dependencies {
    implementation(libs.kotlinx.serialization.core)
}

afterEvaluate {
    publishing {
        publications {
            register("mavenRelease", MavenPublication::class) {
                groupId = "com.kyant"
                artifactId = "tag"
                version = "2023.8.2"
                from(components["release"])
            }
        }
    }
}

package com.kyant.tagapp

import android.os.Build
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.isSystemInDarkTheme
import androidx.compose.foundation.layout.WindowInsets
import androidx.compose.foundation.layout.asPaddingValues
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.systemBars
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material3.Divider
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.darkColorScheme
import androidx.compose.material3.lightColorScheme
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.core.view.WindowCompat
import com.kyant.tag.Tag
import java.io.File
import kotlin.streams.toList as kotlinToList

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        WindowCompat.setDecorFitsSystemWindows(window, false)

        val tags = try {
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
                File("/storage/emulated/0/Music").listFiles()
                    ?.toList()
                    ?.parallelStream()
                    ?.map { Tag.getTag(it.path) }
                    ?.kotlinToList()
            } else {
                File("/storage/emulated/0/Music").listFiles()
                    ?.toList()
                    ?.map { Tag.getTag(it.path) }
            }?.filterNotNull()
        } catch (_: Exception) {
            null
        } ?: emptyList()

        setContent {
            MaterialTheme(colorScheme = if (isSystemInDarkTheme()) darkColorScheme() else lightColorScheme()) {
                Surface {
                    LazyColumn(contentPadding = WindowInsets.systemBars.asPaddingValues()) {
                        item {
                            Text(
                                text = "/Music",
                                modifier = Modifier.padding(24.dp, 96.dp, 24.dp, 32.dp),
                                style = MaterialTheme.typography.headlineLarge,
                            )
                        }
                        items(tags) { tag ->
                            Text(
                                text = tag.toString(),
                                modifier = Modifier.padding(horizontal = 24.dp),
                                style = MaterialTheme.typography.bodyMedium,
                            )
                            Divider(modifier = Modifier.padding(24.dp))
                        }
                    }
                }
            }
        }
    }
}

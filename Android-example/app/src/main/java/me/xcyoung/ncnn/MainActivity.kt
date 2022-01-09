package me.xcyoung.ncnn

import android.graphics.BitmapFactory
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import java.io.File
import java.io.FileOutputStream

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val reco = Reco()

        copy2SD("demo.bin")
        copy2SD("demo.param")
        copy2SD("demo.jpg")
        val externalFile = this.applicationContext.getExternalFilesDir(null)!!
        reco.init(
            externalFile.absolutePath + "/demo.param",
            externalFile.absolutePath + "/demo.bin"
        )

        val bitmap = BitmapFactory.decodeFile(externalFile.absolutePath + "/demo.jpg")
        reco.reco(bitmap)
    }

    private fun copy2SD(name: String) {
        val externalFile = this.applicationContext.getExternalFilesDir(null)!!
        val targetFile = File(externalFile, name)
        if (!targetFile.exists()) {
            targetFile.createNewFile()
        } else {
            return
        }
        val output = FileOutputStream(targetFile.absolutePath)
        val input = assets.open(name)
        val buffer = ByteArray(1024)
        var length = input.read(buffer)
        while (length > 0) {
            output.write(buffer, 0, length)
            length = input.read(buffer)
        }
        output.flush()
        input.close()
        output.close()
    }
}
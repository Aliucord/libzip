# libzip
Simple jni binding for [kuba--/zip](https://github.com/kuba--/zip) lib to be used on Android.

Sample usage
```java
        String data = "File content";

        Zip zip = new Zip(getFilesDir() + "/test.zip", 6, 'w');

        zip.openEntry("test.txt");
        byte[] bytes = data.getBytes();
        zip.writeEntry(bytes, bytes.length);
        zip.closeEntry();

        zip.close();
```

### How to use
Download latest release from releases page to `libs` directory of your project and add this line to `dependencies` section in `build.gradle`:
```js
implementation fileTree(include: '*.aar', dir: './libs')
```

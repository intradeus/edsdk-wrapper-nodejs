This repo is forked from the amazing [Olliebrown's repo](https://github.com/Olliebrown/napi-canon-cameras), which is itself forked from [dimensional-de's repo](https://github.com/dimensional-de/napi-canon-cameras).

Thanks a lot to both of them for their work. I'm just cleaning, testing different versions and OS and merging everything together.

# EDSDK (Canon camera) wrapper module for Node.js
* [Build Package](#build-package)
* [Features](#features)
* [Usage Example](#usage)
* [NPM Tasks](#npm-tasks)
* [FAQ](#faq)
* [API Documentation](API.md)

## Build Package
### WINDOWS | EDSDK v13.14.40 | Tested with Node v[14.16.0, 16.13.0]
The package does not include the Canon EDSDK files. To install the package you will have 
to build a TGZ.

 1. Make sure you are using a tested version of Node and the EDSDK - (the compiled package will work with certain versions, depending on the versions used... it's quite random) 
 2. Download the Canon EDSDK v13.14.40 from [Canon's developer community website](https://developercommunity.usa.canon.com/canon?id=sdk_download)
 3. Unzip the file and copy both the EDSDK and EDSDK_64 folders into `./third_party/EDSDK/Windows/`
 4. Open the file  `./third_party/EDSDK/Windows/EDSDK/Header/EDSDKTypes.h` and replace the lines 865 to 873 by this code snippet
    ```cpp
    typedef enum
    {
        kEdsObjectFormat_Unknown   = 0x00000000,
        kEdsObjectFormat_Jpeg      = 0x3801,
        kEdsObjectFormat_CR2       = 0xB103,
        kEdsObjectFormat_MP4       = 0xB982,
        kEdsObjectFormat_CR3       = 0xB108,
        kEdsObjectFormat_HEIF_CODE = 0xB10B,
    } EdsObjectFormat;
    ```
 5. Run `npm ci`
 6. Run `npm run package`
 7. Copy the generated folder `@dimensional` located at `./node_packages/@dimensional` into your own project's root directory (let's say in a `./sdk_wrapper` folder) 
 8. In your project, install it with `npm i ./sdk_wrapper/@dimensional/napi-canon-cameras.tgz`


## Features

The EDSDK provides a lot of features and not all of them are
implemented in the module. Your use cases might be different.

- [x] List Cameras
- [x] Camera Events
- [ ] Read Camera Properties
    - [x] Text
    - [x] Integer
      - [x] Flags (true/false)
      - [x] Options (named list values)
      - [x] Aperture
      - [x] Shutter Speed
      - [x] Exposure Compensation
    - [x] Integer Array
    - [x] Time
- [ ] Write Camera Properties
    - [ ] Text Properties
    - [x] Integer
    - [ ] Integer Array
    - [ ] Time
- [x] Take Picture
    - [x] Download To Directory
    - [x] Download To File
    - [x] Download To String (Base64)
- [x] Live View
- [ ] Storage
    - [x] List Volumes
    - [x] List Directories and Files
    - [x] Download Thumbnail
    - [x] Download Files


## Usage

```typescript
import {
    Camera, CameraProperty, FileChangeEvent, ImageQuality,
    Option,
    watchCameras
} from '../';

process.on('SIGINT', () => process.exit());

// catch download request events
cameraBrowser.setEventHandler(
    (eventName, event) => {
        if (eventName === CameraBrowser.Events.DownloadRequest) {
            const file = (event as DownloadRequestEvent).file;
            console.log(file);
            const localFile = file.downloadToPath(__dirname + '/images');
            console.log(`Downloaded ${file.name}.`);

            process.exit();
        }
    }
);

// get first camera
const camera = cameraBrowser.getCamera();
if (camera) {
    console.log(camera);
    camera.connect();
    // configure
    camera.setProperties(
        {
            [CameraProperty.ID.SaveTo]: Option.SaveTo.Host,
            [CameraProperty.ID.ImageQuality]: ImageQuality.ID.LargeJPEGFine,
            [CameraProperty.ID.WhiteBalance]: Option.WhiteBalance.Fluorescent
        }
    );
    // trigger picture
    camera.takePicture();
} else {
    console.log('No camera found.');
}

// watch for camera events
watchCameras();
```
 
## NPM Tasks

* `package` - Create TGZ package for AddOn
* `prebuild` - Build for 32 and 64bit Node.js
* `prebuild:x64` - Build for 64bit Node.js
* `prebuild:ia32` - Build for 32bit Node.js
* `build:docs` - Update API documentation in README.md
* `build:stubs` - Update and build stubs (needs prebuild AddOn)
* `clean` - Remove build artifacts

## FAQ
- Getting the following error :
    ```
    gyp: C:\Users\{XXXX}~1\AppData\Local\Temp\prebuildify\node\16.0.0\common.gypi not found (cwd: H:\-Redacted-\edsdk-wrapper-nodejs) while reading includes of binding.gyp while trying to load binding.gyp
    gyp ERR! configure error 
    gyp ERR! stack Error: `gyp` failed with exit code: 1
    ```
    This can happen if you're using nvm. To solve, go to `C:\Users\{XXXX}~1\AppData\Local\Temp` and manually delete the `prebuildify` folder

### Does the module work in Electron Applications?

Yes.


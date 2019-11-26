{
    'targets': [{
        'target_name': 'meow_hash_node',
        '!cflags': [ '-fno-exceptions', '-O3', '-mavx', '-maes', '-msse4' ],
        '!cflags_cc!': [ '-fno-exceptions', '-O3', '-mavx', '-maes', '-msse4' ],
        'sources': [
            'lib/cpp/meow_hash_native_stream.cpp',
            'lib/cpp/main.cpp'
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")",
            "lib/include/",
            "lib/headers/"
        ],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'libraries': [],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS', 'NAPI_EXPERIMENTAL' ],
        'conditions': [
            [
                'OS=="mac"', {
                    'xcode_settings': {
                        'OTHER_CFLAGS': [
                            '-mavx',
                            '-maes',
                            '-O3',
                            '-msse4.1'
                        ]
                    },
                }
            ]
        ]
    }]
}

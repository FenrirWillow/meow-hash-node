{
    'targets': [{
        'target_name': 'meow_hash_node',
        '!cflags': [ '-fno-exceptions', '-O3', '-mavx', '-maes' ],
        '!cflags_cc!': [ '-fno-exceptions', '-O3', '-mavx', '-maes' ],
        'sources': [
            'lib/cpp/main.cpp'
        ],
        'include_dirs': [
            '<!@(node -p \'require("node-addon-api").include\')'
        ],
        'libraries': [],
        'dependencies': [
            '<!(node -p \'require("node-addon-api").gyp\')'
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS', 'NAPI_EXPERIMENTAL' ],
        'conditions': [
            [
                'OS=="mac"', {
                    'xcode_settings': {
                        'OTHER_CFLAGS': [
                            '-mavx',
                            '-maes',
                            '-O3'
                        ]
                    },
                }
            ]
        ]
    }]
}

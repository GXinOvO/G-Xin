1. 源码克隆git@github.com:huggingface/tokenizers.git

2. 将工作空间设置到bingdings/python下

3. 安装一个gdb版本python，如果是ubuntu系统命令如下：(python版本按自己喜好)

   > apt-get install python3.10-dbg

4. 创建虚拟环境（应该也可以不需要，按照tokenizers仓库下python文件夹中readme文件中需要操作，这样方便些）(如果没有venv，直接通过apt下载)

   > python3.10-dbg -m venv .env
   >
   > source .env/bin/activate

5. 编译安装python库（方便一些，直接帮你下载python依赖了）

   > pip install -e .

6. 下载rust, (默认安装就行了)

   > curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

   如果慢的话，执行下面命令配置镜像源

   > export RUSTUP_DIST_SERVER=https://mirrors.ustc.edu.cn/rust-static
   >
   > export RUSTUP_UPDATE_ROOT=https://mirrors.ustc.edu.cn/rust-static/rustup

7. 在bingdings/python文件夹下编译rust项目

   > cargo build

   如果crates下载慢的话配置crates源，在~/.cargo下创建config文件并进行配置(这里激活的科大源)

   ```toml
   [source.crates-io]
   registry = "https://github.com/rust-lang/crates.io-index"
   replace-with = 'ustc'
   
   [source.ustc]
   registry = "git://mirrors.ustc.edu.cn/crates.io-index"
   
   [source.tuna]
   registry = "https://mirrors.tuna.tsinghua.edu.cn/git/crates.io-index.git"
   
   [source.rustcc]
   registry = "https://code.aliyun.com/rustcc/crates.io-index.git"
   
   [http]
   check-revoke = false
   
   [net]
   git-fetch-with-cli=true
   ```

8. 配置完镜像后再次进行编译

9. 安装vscode插件 CodeLLDB(必须安装，用于调试rust)， rust（可以安装，用于rust智能提示等）

10. 进到py_src/tokenizers下，删除掉tokenizers.cpython-xxx-xxx.so(xxx是根据你环境生成的，反正就你知道删除那个)

11. 进到自己rust编译生成的target文件夹中（就在工作空间下），进入到debug(release不行，选择编译debug), 将自己编译生成携带调试信息的.so文件复制过去(注意要改名，前缀lib去掉)

    > mv libtokenizers.so ../../py_src/tokenizers/tokenizers.so

12. 配置lauch.json, 在当前工作文件夹下创建.vscode。新建launch.json文件

```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Attach",
            "type": "lldb",
            "request": "launch",
            "program": "/workspace/tokenizers/bindings/python/.env/bin/python",
            "args": [
                "tests/custome_test.py"   
            ],
            // "MIMode": "gdb",
            "cwd": "."
        }
    ]
}
```

13. 调试即可，记得在你需要调试的pyo3绑定接口上打断点





**注意：这个有一个小坑，你自己解决一下，就是从github仓库克隆编译的tokenizers版本是最新的，超出了tokenizers这个项目的一个python第三方库transformers要求的tokenizers版本，可能在调试某些接口时出问题，但是调试你的batch_encode没问题，（huggingface的失误）**

**注意：这种方式确实是从python文件进入到rust，但是没办法断点调试pyton文件，因为python调试依赖于pdb，而rust依赖于lldb，俩个不一样调试器，如果还想断点调试python，可以再开一个python调试进程**
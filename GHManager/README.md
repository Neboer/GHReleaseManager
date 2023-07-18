每个GHRProgram都唯一对应一个来自Github Release的二进制程序包。
Github程序包有如下属性：
不变属性，这些属性不会变化，在添加仓库时需要提供。
- 仓库名 repo_name
- 安装预览更新 pre_release
- 目标文件名匹配规则 target_file_pattern
- 仓库版本信息提取规则 repo_version_pattern
- 安装命令 install_script
- 是否启用更新 enable_update
变化属性，这些属性会随更新自动变化
- 本地安装版本 local_version
- 仓库最新版本 remote_version
- 仓库最新preview版本 remote_preview_version
- 最后一次检查更新时间 last_check_update_time
- 安装时间 last_install_time
## 文件结构
GHManager中的C位是GHManager类，与文件同名。只有这个类中存在可以和网络沟通的Github API对象。
GHRepoRelease和GHRProgram都是对应的数据结构，程序只需要引入GHManager即可。
#!/bin/bash
# ===== CLAW 龙虾配置同步脚本 =====
# 用法：
#   sh CLAW/工具/sync_push.sh    ← 这台：配置拷进仓库+推送
#   sh CLAW/工具/sync_pull.sh    ← 另一台：拉取+配置应用到龙虾

REPO="/mnt/c/Users/qlz15/Desktop/CPP"
SYNC_DIR="$REPO/CLAW/龙虾同步"
WORKSPACE="$HOME/.openclaw/workspace"

case "${1:-push}" in
  push)
    echo "📤 将龙虾配置同步到仓库..."
    cp "$WORKSPACE/AGENTS.md" "$SYNC_DIR/" 2>/dev/null && echo "  ✅ AGENTS.md"
    cp "$WORKSPACE/SOUL.md" "$SYNC_DIR/" 2>/dev/null && echo "  ✅ SOUL.md"
    cp "$WORKSPACE/USER.md" "$SYNC_DIR/" 2>/dev/null && echo "  ✅ USER.md"
    cp "$WORKSPACE/TOOLS.md" "$SYNC_DIR/" 2>/dev/null && echo "  ✅ TOOLS.md"
    cp "$WORKSPACE/IDENTITY.md" "$SYNC_DIR/" 2>/dev/null && echo "  ✅ IDENTITY.md"

    cd "$REPO"
    git add CLAW/龙虾同步/ CLAW/模板/ CLAW/2026/ 2>/dev/null
    git add -u CLAW/ 2>/dev/null

    echo ""
    read -p "📝 提交说明（直接回车=默认）：" msg
    msg="${msg:-🔄 同步龙虾配置}"
    git commit -m "$msg"
    git push
    echo "✅ 推送完成！另一台电脑 pull 后跑 sync_pull.sh 即可"
    ;;

  pull)
    echo "📥 从仓库拉取龙虾配置..."
    cd "$REPO"
    git pull

    echo ""
    echo "📋 以下文件将覆盖到龙虾工作区："
    for f in AGENTS.md SOUL.md USER.md TOOLS.md IDENTITY.md; do
      [ -f "$SYNC_DIR/$f" ] && echo "  🔄 $f"
    done

    read -p "是否应用？(y/N): " confirm
    if [ "$confirm" = "y" ] || [ "$confirm" = "Y" ]; then
      for f in AGENTS.md SOUL.md USER.md TOOLS.md IDENTITY.md; do
        [ -f "$SYNC_DIR/$f" ] && cp "$SYNC_DIR/$f" "$WORKSPACE/" && echo "  ✅ $f 已应用"
      done
      echo "🎉 配置同步完成！"
    else
      echo "⏭️ 跳过"
    fi
    ;;

  *)
    echo "用法: sh CLAW/工具/sync_push.sh [push|pull]"
    echo "  push  - 本机配置 → 仓库（默认）"
    echo "  pull  - 仓库配置 → 本机"
    ;;
esac

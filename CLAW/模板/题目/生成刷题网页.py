#!/usr/bin/env python3
# 从 习题_老师.md + 习题_答案与解析.md 解析生成刷题网页（保证与习题完全一致）
import re, json

TPL = '/mnt/c/Users/41525/Desktop/CPP/CLAW/模板/题目/刷题网页_模板.html'
tpl = open(TPL, encoding='utf-8').read()

def md2html(s):
    """md 反引号 → <code>，**加粗** → <b>"""
    s = re.sub(r'`([^`]+)`', r'<code>\1</code>', s)
    s = re.sub(r'\*\*([^*]+)\*\*', r'<b>\1</b>', s)
    return s.strip()

def parse_teacher(md):
    """解析习题_老师.md → {题号: {type, question, options}}"""
    qs = {}
    blocks = re.split(r'###### \*\*(\d+)\.\*\*', md)
    for i in range(1, len(blocks), 2):
        num = int(blocks[i])
        body = blocks[i+1]
        # 判断题：题目带（ ）且无 A. 选项
        m_judge = re.match(r'\s*(.*?)（\s*）', body, re.S)
        if m_judge and not re.search(r'\n\s*A\.', body):
            q = m_judge.group(1).strip()
            qs[num] = {'type': 'judge', 'question': md2html(q), 'options': []}
        else:
            m_q = re.match(r'\s*(.*?)\n\s*A\.', body, re.S)
            q = m_q.group(1).strip() if m_q else body.strip()[:50]
            opts = re.findall(r'\n([ABCD])\.\s*(.*)', body)
            opts = [o.strip() for _, o in opts]
            qs[num] = {'type': 'single', 'question': md2html(q), 'options': opts}
    return qs

def parse_answer(md):
    """解析习题_答案与解析.md → {题号: {answer, expl_text}}"""
    res = {}
    # 按题分块：**N.** 答案 **X**
    blocks = re.split(r'\*\*(\d+)\.\*\*\s*答案\s*\*\*([A-Z✅❌TF ]+)\*\*', md)
    # blocks: [pre, '1', 'B', 内容, '2', 'A', 内容, ...]
    for i in range(1, len(blocks), 3):
        num = int(blocks[i])
        ans = blocks[i+1].strip().replace('✅', '').replace('❌', '').strip()
        body = blocks[i+2]
        # 选项分析表行：| A | 分析 |
        analyses = []
        for m in re.finditer(r'\|\s*([ABCD])\s*([✅❌]?)\s*\|\s*([^|]+)\|', body):
            letter, mark, text = m.group(1), m.group(2), m.group(3).strip()
            analyses.append(f"{letter}{'✅' if '✅' in mark else ''}：{text}")
        # 考点
        km = re.search(r'>\s*考点：\s*(.*)', body)
        expl = '；'.join(analyses)
        if km:
            expl += f'【考点：{km.group(1).strip()}】'
        res[num] = {'answer': ans, 'expl': expl}
    return res

def generate(outpath, title, subtitle, teacher_md, answer_md, password):
    teacher = parse_teacher(teacher_md)
    answers = parse_answer(answer_md)
    items = []
    expl = {}
    for num in sorted(teacher.keys()):
        q = teacher[num]
        a = answers.get(num, {'answer': 'A', 'expl': ''})
        if q['type'] == 'judge':
            answer = 'A' if a['answer'].upper() in ('T', '对') else 'B'
            items.append({'id': num, 'type': 'judge', 'question': q['question'],
                          'options': ["✓ 正确", "✗ 错误"], 'answer': answer, 'score': 2})
        else:
            items.append({'id': num, 'type': 'single', 'question': q['question'],
                          'options': [f"{chr(65+i)}. {o}" for i, o in enumerate(q['options'])],
                          'answer': a['answer'].upper(), 'score': 2})
        expl[num] = a['expl']
    # 生成 HTML
    h = tpl
    h = re.sub(r'<title>.*?</title>', f'<title>{title}</title>', h)
    h = re.sub(r'<h1>.*?</h1>', f'<h1>{title}</h1>', h, count=1)
    h = re.sub(r'<div class="app-header">\s*<h1>.*?</h1>\s*<p>.*?</p>',
               f'<div class="app-header">\n  <h1>{title}</h1>\n  <p>{subtitle}</p>', h, flags=re.S)
    h = re.sub(r'const QUESTION_BANK = \[[\s\S]*?\];',
               'const QUESTION_BANK = ' + json.dumps(items, ensure_ascii=False) + ';', h, count=1)
    h = re.sub(r'const PASSWORD = "[*]+";', f'const PASSWORD = "{password}";', h)
    h = re.sub(r'const EXPLANATIONS = \{[\s\S]*?\};',
               'const EXPLANATIONS = ' + json.dumps(expl, ensure_ascii=False) + ';', h, flags=re.S, count=1)
    total = len(items) * 2
    h = h.replace('${每题分}', '2').replace('${总分}', str(total))
    open(outpath, 'w', encoding='utf-8').write(h)
    print('✅', outpath)

# ============================================================
# 使用说明（2026-08-05）
# 刷题网页必须从习题 md 解析生成（单一数据源，保证与习题同步）
# 步骤：
#   1. 在下方 TASKS 中添加/修改配置（文件夹名、网页标题、副标题、6位密码）
#   2. 运行: python3 CLAW/模板/题目/生成刷题网页.py
#   3. 检查输出无 ❌；密码记入 CLAW/2026/快速查找.md
# 数据源: 各套文件夹内的 习题_老师.md（题目+选项）与 习题_答案与解析.md（答案+解析）
# ============================================================
BASE = '/mnt/c/Users/41525/Desktop/CPP/CLAW/2026'
TASKS = [
    # (文件夹相对路径, 网页标题, 副标题, 密码)
    ('7_30_1_树的理论/第4套练习-树1树2综合A', '树 综合练习 · 第4套（A卷）',
     '树与二叉树 · 完全/满二叉树 · 遍历还原 · 表达式 · BST · 哈夫曼树', '480425'),
    ('7_30_1_树的理论/第5套练习-树1树2综合B', '树 综合练习 · 第5套（B卷）',
     '树与二叉树 · 完全/满二叉树 · 遍历还原 · 表达式 · BST · 哈夫曼树', '580525'),
]

for folder, title, subtitle, pw in TASKS:
    generate(
        f'{BASE}/{folder}/刷题.html',
        title, subtitle,
        open(f'{BASE}/{folder}/习题_老师.md', encoding='utf-8').read(),
        open(f'{BASE}/{folder}/习题_答案与解析.md', encoding='utf-8').read(),
        pw)

<script lang="ts" setup>
import { ref } from 'vue'

let name = ref('尚硅谷')
let age = ref(18)

defineExpose({ name, age })

</script>

<template>
    <div>
        <h2>姓名：{{ name }}</h2>
        <h2>年龄：{{ age }}</h2>
        <br>
    </div>
</template>

<style scoped></style>
